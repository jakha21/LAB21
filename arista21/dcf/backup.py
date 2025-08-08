#!/home/jakha/LAB21/.vnetauto/bin/python3

"""
This script retrieves running configurations from Arista EOS devices and saves them to text files.
"""

import pyeapi


def connect_to_device(NODE):
    """Connects to an EOS device and returns the device instance."""

    try:
        return pyeapi.connect_to(NODE)
    except pyeapi.eapi_errors.ConnectionError as err:
        print(f"Failed to connect to device {NODE}: {err}")
        return None


def get_running_config(DEVICE):
    """Gets the running configuration from an EOS device as a string."""

    try:
        return '\n'.join(DEVICE.get_config('running-config'))
    except pyeapi.eapi_errors.ConnectionError as err:
        print(f"Failed to connect to device {NODE}: {err}")
        return ""


def write_to_file(FILENAME, CONTENT):
    """Writes content to a file."""

    try:
        with open(FILENAME, '+w') as file:
            file.write(CONTENT)
    except Exception as err:
        print(f"Failed to write to file {FILENAME}: {err}")


if __name__ == "__main__":
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

    for NODE in NODES:
        DEVICE = connect_to_device(NODE)
        if DEVICE:  # Check if connection successful before proceeding
            try:
                CONTENT = get_running_config(DEVICE)
                FILENAME = f'backups/{pyeapi.config_for(NODE)["host"]}.cfg'  # Use config_for for IP retrieval
                write_to_file(FILENAME, CONTENT)
            except Exception as err:
                print(f"Unexpected error occurred: {err}")  # Print critical errors
        else:
            pass
