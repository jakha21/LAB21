#!/usr/bin/python3

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
    NODES = ['Spine-1', 'Spine-2', 'Leaf-1', 'Leaf-2', 'Leaf-3', 'Leaf-4']

    for NODE in NODES:
        DEVICE = connect_to_device(NODE)
        if DEVICE:  # Check if connection successful before proceeding
            try:
                CONTENT = get_running_config(DEVICE)
                FILENAME = f'{pyeapi.config_for(NODE)["host"]}-config.txt'  # Use config_for for IP retrieval
                write_to_file(FILENAME, CONTENT)
            except Exception as err:
                print(f"Unexpected error occurred: {err}")  # Print critical errors
        else:
            pass
