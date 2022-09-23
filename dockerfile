# build run env
FROM ubuntu:22.04

ENV TZ = Asia/Shanghai

WORKDIR /usr/local/src

RUN apt-get update -y && apt-get install -y libelf1 libelf-dev zlib1g-dev clang python-is-python3 make llvm

COPY ./. /usr/local/src

VOLUME /data/

ENTRYPOINT ["/bin/bash","-l","-c"]
CMD ["make build"]
