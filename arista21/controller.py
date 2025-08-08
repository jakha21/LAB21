#!/home/jakha/LAB21/.vnetauto/bin/python3
"""
Arista EOS network automation with pyeapi.
"""

import pyeapi
from pprint import pprint

NODES = {
    'bleaves' : ['border_leaf1', 'border_leaf2'],
    'spines' : ['spine1', 'spine2', 'spine3', 'spine4'],
    'leaves' : ['leaf1', 'leaf2', 'leaf3', 'leaf4', 'leaf5', 'leaf6']
    }

def connect_to_device(NODE):
    """Connects to an EOS device and returns the device instance."""
    try:
        return pyeapi.connect_to(NODE)
    except Exception as err:
        print(f"Failed to connect to device {NODE}: {err}")
        return None

def bgp_config(NODE):
    """Configures BGP on the specified node."""
    DEVICE = connect_to_device(NODE)
    if DEVICE:
        try:
            NODE.api.bgp.create('4230036002')  # Create BGP instance
        except Exception as err:
            print(f"Failed to create BGP instance on {NODE}: {err}")

for NODE in NODES['leaves']:
    DEVICE = connect_to_device(NODE)
    commands = ['interface management0', 'description MGMT']
    if DEVICE:  # Check if connection successful before proceeding
        try:
#            DEVICE.config(commands)  # Apply configuration commands
            output = DEVICE.enable('show bgp summary')  # Retrieve interface description
            pprint(output[0]['result'])  # Print the running configuration commands

        except Exception as err:
            print(f"Unexpected error occurred: {err}")  # Print critical errors
    else:
        pass

bgp_config('leaf2')  # Example of configuring BGP on a specific node