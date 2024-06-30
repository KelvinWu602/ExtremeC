sudo rm lib/process-created.txt
sudo ./lib/open_create_file

# When a process is started by the root user, it's real uid == 0.
# By default, the effective uid == real uid. This define what the process can do.
# By default, the filesystem uid == effective user id. This define what files the process can access.

# The file created by the process will have uid == filesystem uid.