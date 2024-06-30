# create a test user with its home directory
sudo useradd -m -d "$(pwd)/lib/testuserhome" -s /bin/bash -u 1001 testuser
# create a file owned by it
sudo su -c 'echo "testuser-owned" > ~/testuser-own' testuser
# change mode to only testuser itself can read write
sudo su -c "chmod 0600 ~/testuser-own" testuser

# try to read the testuser-own file, should get permission denied
cat lib/testuserhome/testuser-own

# run the user program which set its filesystem uid as normal user uid (1000), this proves that process's file access right is evaluated on fsuid, not euid
sudo ./lib/testuser_fsuid_read_file

# remove the test-user and its file
sudo userdel -rf testuser
