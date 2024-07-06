# Use an official Ubuntu as a parent image
FROM ubuntu:24.04

# Set the environment variable for non-interactive installation
ENV DEBIAN_FRONTEND=noninteractive

# Install the necessary packages
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    gcc \
    g++ \
    wget \
    git \
    curl \
    clang \
    clang-format \
    libstdc++-13-dev \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory in the container
WORKDIR /app


RUN curl -fsSL https://deb.nodesource.com/setup_20.x | bash - && \
    apt-get install -y nodejs && \
    node -v && npm -v
