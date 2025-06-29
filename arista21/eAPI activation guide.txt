Step 1: Make sure all devices have IP reachability and remote access.
Step 2: Enable eAPI by issuing "management api http-commands no shutdown" command on all devices.
Step 3: Create the "eapi.conf" file, add default connection info such as transport method/user credentials and save it in "/mnt/flash" directory.
Step 4: Create an enviroment variable so that scripts can retrieve connection info from "eapi.conf" file.
sudo nano ~/.bashrc
export EAPI_CONF=/path/to/eapi.conf
source ~/.bashrc
Step 5: Create a node object and specify the hostname(s) of device(s) you want to manage.
node = pyeapi.connect_to('hostname)
