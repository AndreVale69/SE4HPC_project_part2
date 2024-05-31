# SingularityCE

# 1. [Install Dependencies](https://docs.sylabs.io/guides/4.1/admin-guide/installation.html#install-dependencies)

### Ensure repositories are up-to-date
```bash
sudo apt-get update
```

### Install ubuntu packages for dependencies
```bash
sudo apt-get install -y \
   autoconf \
   automake \
   cryptsetup \
   fuse \
   fuse2fs \
   git \
   libfuse-dev \
   libglib2.0-dev \
   libseccomp-dev \
   libtool \
   pkg-config \
   runc \
   squashfs-tools \
   squashfs-tools-ng \
   uidmap \
   wget \
   zlib1g-dev
```

-----------------------------------------------------------

# 2. [Install Go](https://docs.sylabs.io/guides/4.1/admin-guide/installation.html#install-go)

### Install [Go](https://go.dev/dl/)
```bash
export VERSION=1.21.10 OS=linux ARCH=amd64
wget https://dl.google.com/go/go$VERSION.$OS-$ARCH.tar.gz
sudo tar -C /usr/local -xzvf go$VERSION.$OS-$ARCH.tar.gz
rm go$VERSION.$OS-$ARCH.tar.gz
```


### Set up environment for Go
```bash
echo 'export GOPATH=${HOME}/go' >> ~/.bashrc
echo 'export PATH=/usr/local/go/bin:${PATH}:${GOPATH}/bin' >> ~/.bashrc
source ~/.bashrc
```
-----------------------------------------------------------

# 3. [Download SingularityCE from a release](https://docs.sylabs.io/guides/4.1/admin-guide/installation.html#download-singularityce-from-a-release)

[GitHub release page](https://github.com/sylabs/singularity/releases)

### Download SingularityCE from a release
```bash
export VERSION=4.1.3
wget https://github.com/sylabs/singularity/releases/download/v${VERSION}/singularity-ce-${VERSION}.tar.gz
tar -xzf singularity-ce-${VERSION}.tar.gz
cd singularity-ce-${VERSION}
```

-----------------------------------------------------------

# 4. [Compile Singularity](https://docs.sylabs.io/guides/4.1/admin-guide/installation.html#compile-singularity)

### Compile Singularity
```bash
./mconfig
make -C ./builddir
sudo make -C ./builddir install
```

-----------------------------------------------------------

# Optional. [Testing & Checking the Build Configuration](https://docs.sylabs.io/guides/4.1/admin-guide/installation.html#testing-checking-the-build-configuration)

### Testing & Checking the Build Configuration
```bash
singularity exec library://alpine cat /etc/alpine-release
```