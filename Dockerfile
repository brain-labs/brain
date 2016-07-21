FROM jbrooker/clang-toolchain:latest

RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y ssh-client
RUN apt-get install -y git
RUN apt-get install -y build-essential
RUN apt-get install libtinfo-dev
RUN apt-get install -y zlib1g-dev
RUN apt-get install -y libedit-dev

RUN git clone https://github.com/luizperes/brain.git /root/brain
RUN cd /root/brain && git checkout dev && make SUDO?=

ENV PATH $PATH:/root/brain/bin
RUN alias brain=/root/brain/bin/brain

