# build run env
FROM ubuntu:22.04

ENV TZ = Asia/Shanghai

WORKDIR /usr/local/src

RUN apt-get update -y && apt-get upgrade -y && apt-get install -y libssl-dev libcurl4-openssl-dev libcurl4 libelf-dev

RUN apt-get install cmake -y

RUN apt-get install clang -y
RUN apt-get install llvm -y

COPY ./. /usr/local/src

RUN cp ./test/*.bpf.c client.bpf.c && cp ./test/*.bpf.h event.h && cp ./test/config.json config.json

RUN make

VOLUME /data/

ENTRYPOINT ["/bin/bash","-l","-c"]
CMD ["cp .output/package.json /data/"]
