#!/home/jakha/LAB21/.vnetauto/bin/python3
"""
Arista EOS network automation with pyeapi.
"""

import pyeapi
from pprint import pprint

NODES = ['border_leaf1', 
        'border_leaf2', 
        'spine1', 
        'spine2', 
        'spine3', 
        'spine4',
        'leaf1', 
        'leaf2', 
        'leaf3', 
        'leaf4', 
        'leaf5', 
        'leaf6']

def connect_to_device(NODE):
    """Connects to an EOS device and returns the device instance."""
    try:
        return pyeapi.connect_to(NODE)
    except Exception as err:
        print(f"Failed to connect to device {NODE}: {err}")
        return None

for NODE in NODES:
    DEVICE = connect_to_device(NODE)
    commands = ['write memory']
    if DEVICE:  # Check if connection successful before proceeding
        try:
            DEVICE.config(commands)  # Apply configuration commands
            output = DEVICE.enable('show interfaces description')  # Retrieve interface description
            pprint(output[0]['result']['interfaceDescriptions']['Management0']['description'])  # Print the running configuration commands

        except Exception as err:
            print(f"Unexpected error occurred: {err}")  # Print critical errors
    else:
        pass
