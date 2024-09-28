# README #

gRPC-based server-client implementation

### How do I compile? ###

* For aarch64: `./run_aarch64.sh`
* For x86: `./run_x86.sh`
* Dependencies:
    - grpc [Version `1.46.7`]

### How to run ###

* run server
    - export SERVER_ADDRESS=`<server_ip:port>`
    - ./server 
* run client
    - ./client `<server_ip:port>`
