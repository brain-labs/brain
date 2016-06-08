FROM buildpack-deps:vivid-scm

RUN apt-get update

RUN apt-get install -y \
    llvm-3.6 \
    llvm-3.6-doc \
    llvm \
    clang-3.6 \
    clang-3.6-doc \
    clang \
    lldb-3.6 \
    lldb \
    libstdc++-4.9-doc \
    glibc-doc \
    man

RUN apt-get install -y \
    make \
    patch \
    file \
    bzip2

RUN apt-get install -y zlib1g-dev
RUN apt-get install -y libedit-dev
RUN apt-get install -y vim

RUN git clone https://github.com/luizperes/brain.git /root/brain 
RUN cd /root/brain/src && make 

ENV PATH $PATH:/root/brain/src
RUN alias brain=/root/brain/src/brain

