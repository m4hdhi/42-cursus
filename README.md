*This project has been created as part of the 42 curriculum by mamuzamm.*

# NetPractice

## Description

NetPractice is a practical networking project from the 42 curriculum. The goal is to understand the basics of computer networking by fixing simulated network configurations.

In this project, I configured IP addresses, subnet masks, routes, and gateways so that different machines could communicate correctly through switches and routers. The project focuses on understanding how TCP/IP addressing works in small networks.

The training interface contains 10 levels. Each level shows a broken network diagram, and the objective is to modify the available fields until the network works correctly.

## Instructions

### How to run the project

1. Extract the NetPractice files.
2. Open a terminal inside the extracted folder.
3. Run:

```bash
./run.sh
```

4. The training interface should open in the browser.

If `run.sh` does not work, the interface can be started manually with:

```bash
python3 -m http.server 49242
```

Then open this URL in the browser:

```text
http://localhost:49242
```

### How to complete the levels

1. Enter your 42 login in the training interface.
2. Start from Level 1.
3. Read the objective shown at the top of the page.
4. Modify the unshaded configuration fields.
5. Click **Check again** to test the configuration.
6. When the level is correct, click **Get my config** to export the configuration file.
7. Save one exported configuration file for each level.
8. Continue until all 10 levels are completed.

### Submission requirements

The repository must contain:

- This `README.md` file at the repository root.
- 10 exported configuration files, one for each level.
- All exported configuration files must be placed at the root of the Git repository.

Example structure:

```text
.
├── README.md
├── level1.json
├── level2.json
├── level3.json
├── level4.json
├── level5.json
├── level6.json
├── level7.json
├── level8.json
├── level9.json
└── level10.json
```

The exact exported file names may depend on the interface, but all 10 files must be submitted at the repository root.

## Networking Concepts Studied

During this project, I studied and practiced the following networking concepts:

- TCP/IP addressing
- IPv4 addresses
- Subnet masks
- Network addresses
- Host addresses
- Default gateways
- Routers
- Switches
- Routing between different networks
- Local network communication
- OSI model basics
- Packet forwarding

## Quick Notes

An IP address identifies a device on a network.

A subnet mask defines which part of the IP address is the network part and which part is the host part.

A switch connects devices inside the same local network.

A router connects different networks together.

A default gateway is the router address used by a machine when it needs to reach another network.

Two devices can communicate directly only if they are in the same subnet. If they are in different subnets, they need a router and a correct gateway.

## Resources

Useful resources for understanding this project:

- 42 NetPractice subject PDF
- Cisco: Introduction to TCP/IP
- Cloudflare Learning Center: What is an IP address?
- Cloudflare Learning Center: What is a subnet?
- GeeksforGeeks: Subnetting in Computer Networks
- Wikipedia: OSI model
- Wikipedia: Router
- Wikipedia: Network switch

## AI Usage

AI was used as a learning assistant for this project. It helped with:

- Understanding the project requirements.
- Summarizing networking concepts in simple language.
- Preparing this README structure.
- Creating a simple workflow for completing and submitting the project.

AI was not used to replace personal understanding. All networking configurations must be checked, tested, and understood before submission and peer evaluation.
