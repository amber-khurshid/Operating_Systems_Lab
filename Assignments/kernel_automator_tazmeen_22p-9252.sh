#!/bin/bash

# Variables
version="6.11.7"
url="https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-$version.tar.xz"
file_name="linux-$version.tar.xz"
directory="linux-$version"

# Step 1: Download the Linux kernel

echo "Downloading Linux kernel version $version..."
if wget $url -O $file_name; then
    echo "Kernel downloaded successfully."
else
    echo "Failed to download the kernel." 
    exit 1
fi

# Step 2: Verify the integrity of the downloaded file

echo "Verifying the integrity of the downloaded file."
sha256sum $file_name  

# Step 3: Extract the kernel source

echo "Extracting the kernel source."
if tar xvf $file_name; then
    echo "Kernel source extracted successfully."
else
    echo "Failed to extract the kernel source." 
    exit 1
fi

# Change directory to the kernel source

cd $directory || { 
echo "Kernel directory not found";
 exit 1; 
 }

# Step 4: Install dependencies

echo "Installing dependencies."
if sudo apt-get install -y git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison; then
    echo "Dependencies installed successfully."
else
    echo "Failed to install dependencies." 
    exit 1
fi

# Step 5: Configure the kernel

echo "Configuring the kernel."
if cp -v /boot/config-$(uname -r) .config; then
    echo "Existing system configuration copied."
else
    echo "Failed to copy the system configuration." 
    exit 1
fi

# Disable conflicting security certificates

scripts/config --disable SYSTEM_TRUSTED_KEYS
scripts/config --disable SYSTEM_REVOCATION_KEYS


echo "Launching menuconfig for kernel customization..."
if make menuconfig; then
    echo "Kernel configured successfully."
else
    echo "Kernel configuration failed." 
    exit 1
fi


# Step 6: Compile the kernel

echo "Compiling the kernel."
if make -j$(nproc); then
    echo "Kernel compiled successfully."
else
    echo "Kernel compilation failed." 
    exit 1
fi

# Step 7: Install kernel modules

echo "Installing kernel modules."
if sudo make modules_install; 
then
    echo "Kernel modules installed successfully."
else
    echo "Failed to install kernel modules." 
    exit 1
fi

# Step 8: Install the kernel

echo "Installing the kernel."
if sudo make install; then
    echo "Kernel installed successfully."
else
    echo "Kernel installation failed." 
    exit 1
fi

# Step 9: Update the bootloader

echo "Updating the bootloader (GRUB)."
if sudo update-initramfs -c -k $version && sudo update-grub; then
    echo "Bootloader updated successfully."
else
    echo "Failed to update the bootloader." 
    exit 1
fi

# Step 10: Reboot the system

echo "Rebooting the system."
read -p "Press Y to reboot now or N to reboot later: " choice
if [[ $choice == "Y" || $choice == "y" ]]; then
    sudo reboot
else
    echo "Reboot manually to apply the new kernel."
fi

# Verification step after rebooting
# Run: uname -r
# Expected output: $version

