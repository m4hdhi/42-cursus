#!/usr/bin/env bash
#
# 42sync.sh — keep your 42 (vogsphere) projects and ONE combined GitHub repo in sync.
#
# Layout: this script lives in the root of your combined GitHub repo (e.g. "42").
# Each 42 project becomes a folder in this repo, and its vogsphere URL is
# remembered in a .42repos file (managed automatically):
#
#     cpp-module-00  git@vogsphere.42abudhabi.ae:vogsphere/intra-uuid-...-mamuzamm  master
#
# Commands:
#   ./42sync.sh add  <folder> <vogsphere-url> [branch]
#       Import a 42 project into <folder>/ WITH its full commit history,
#       then push to GitHub. Branch defaults to master (vogsphere's default).
#
#   ./42sync.sh pull <folder> | all
#       Bring new commits from vogsphere into this repo, then push to GitHub.
#       Use this when you pushed to 42 from your normal per-project clone.
#
#   ./42sync.sh push <folder>
#       Send this folder's new commits to vogsphere (= submit to 42),
#       then push the whole repo to GitHub. One command, both places.
#
#   ./42sync.sh list
#       Show tracked projects.
#
# Notes:
#   * Get each vogsphere URL from the project's intra page ("GIT REPOSITORY").
#   * 42 evaluations only ever read vogsphere — GitHub is your mirror/portfolio.
#   * Keep each commit inside ONE project folder; that keeps pushes to 42 clean.
#   * Closed/locked projects can still be imported (clone works read-only),
#     they just can't receive pushes on the 42 side anymore.

set -euo pipefail

MAP_FILE=".42repos"

die() { echo "error: $*" >&2; exit 1; }

usage() {
    echo "usage: $0 add <folder> <vogsphere-url> [branch]"
    echo "       $0 pull <folder>|all"
    echo "       $0 push <folder>"
    echo "       $0 list"
    exit 1
}

# ---------- sanity checks ----------------------------------------------------
git rev-parse --show-toplevel >/dev/null 2>&1 \
    || die "run this from inside your combined 42 repo"
cd "$(git rev-parse --show-toplevel)"

if git subtree 2>&1 | grep -qi "is not a git command"; then
    die "'git subtree' is not available in this git installation"
fi

require_clean() {
    git diff-index --quiet HEAD -- 2>/dev/null \
        || die "you have uncommitted changes — commit or stash them first"
}

push_github() {
    if git push origin HEAD; then
        echo "==> mirrored to GitHub"
    else
        echo "(!) could not push to GitHub — run 'git push' manually" >&2
    fi
}

lookup() {  # $1 = folder  ->  sets URL and BRANCH
    [ -f "$MAP_FILE" ] || die "$MAP_FILE not found — import a project first with: $0 add <folder> <url>"
    local line
    line=$(grep -E "^$1[[:space:]]" "$MAP_FILE" | head -n 1 || true)
    [ -n "$line" ] || die "no entry for '$1' in $MAP_FILE (see: $0 list)"
    URL=$(echo "$line" | awk '{print $2}')
    BRANCH=$(echo "$line" | awk '{print $3}')
    BRANCH=${BRANCH:-master}
}

# ---------- commands ---------------------------------------------------------
cmd_add() {
    [ $# -ge 2 ] || usage
    local folder="$1" url="$2" branch="${3:-master}"

    [ -f "$MAP_FILE" ] && grep -qE "^$folder[[:space:]]" "$MAP_FILE" \
        && die "'$folder' is already tracked"
    [ -e "$folder" ] && die "'$folder' already exists in this repo"
    require_clean

    git ls-remote "$url" >/dev/null 2>&1 \
        || die "cannot reach $url — check the URL and your 42 SSH key"

    if git ls-remote --exit-code "$url" "refs/heads/$branch" >/dev/null 2>&1; then
        git subtree add --prefix="$folder" "$url" "$branch"
    else
        echo "==> vogsphere repo has no '$branch' branch yet (new project)"
        echo "    tracking '$folder' — create the folder, commit your work,"
        echo "    then '$0 push $folder' will create it on the 42 side."
    fi

    printf '%s %s %s\n' "$folder" "$url" "$branch" >> "$MAP_FILE"
    git add "$MAP_FILE"
    git commit -q -m "42sync: track $folder" -- "$MAP_FILE"
    push_github
    echo "==> '$folder' is now tracked"
}

pull_one() {
    lookup "$1"
    echo "==> pulling $1 from 42..."
    git subtree pull --prefix="$1" "$URL" "$BRANCH" -m "42sync: sync $1 from vogsphere"
}

cmd_pull() {
    [ $# -ge 1 ] || usage
    require_clean
    if [ "$1" = "all" ]; then
        local f
        while read -r f _; do
            [ -n "$f" ] && pull_one "$f"
        done < "$MAP_FILE"
    else
        pull_one "$1"
    fi
    push_github
}

cmd_push() {
    [ $# -ge 1 ] || usage
    lookup "$1"
    require_clean
    echo "==> pushing $1 to 42 (vogsphere)..."
    git subtree push --prefix="$1" "$URL" "$BRANCH"
    push_github
    echo "==> done: submitted to 42 AND mirrored on GitHub"
}

cmd_list() {
    [ -f "$MAP_FILE" ] || { echo "no projects tracked yet"; exit 0; }
    column -t "$MAP_FILE" 2>/dev/null || cat "$MAP_FILE"
}

# ---------- dispatch ---------------------------------------------------------
[ $# -ge 1 ] || usage
cmd="$1"; shift
case "$cmd" in
    add)  cmd_add "$@" ;;
    pull) cmd_pull "$@" ;;
    push) cmd_push "$@" ;;
    list) cmd_list ;;
    *)    usage ;;
esac
