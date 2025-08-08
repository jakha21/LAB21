#!/home/jakha/LAB21/.vnetauto/bin/python3
import pyeapi

NODES = ['border_leaf1', 'border_leaf2', 'spine1', 'spine2', 'spine3', 'spine4', 'leaf1', 'leaf2', 'leaf3', 'leaf4', 'leaf5', 'leaf6']

def instantiate_node(NODE):
    """Connects to an EOS device and returns the device instance."""
    try:
        return pyeapi.connect_to(NODE)
    except Exception as err:
        print(f"Failed to connect to device {NODE}: {err}")
        return None

def get_mgmt_ip(NODE):
    """Retrieves the IP address of the management interface."""
    DEVICE = instantiate_node(NODE)
    if DEVICE:
        try:
            mgmt = DEVICE.enable('show ip interface management0')
            return mgmt[0]['result']['interfaces']['Management0']['interfaceAddressBrief']['ipAddr']['address']
        except Exception as err:
            print(f"Failed to retrieve IP address for {NODE}: {err}")
            return None
    return None

def get_loopback_ip(NODE):
    """Retrieves the IP address of the loopback interface."""
    DEVICE = instantiate_node(NODE)
    if DEVICE:
        try:
            loop = DEVICE.enable('show ip interface Loopback0')
            return loop[0]['result']['interfaces']['Loopback0']['interfaceAddressBrief']['ipAddr']['address']
        except Exception as err:
            print(f"Failed to retrieve loopback IP address for {NODE}: {err}")
            return None
    return None

def get_ip(NODE):
    """Retrieves the IP address of the specified node."""
    DEVICE = instantiate_node(NODE)
    if DEVICE:
        try:
            return DEVICE.api('ipinterfaces').get(name='Loopback0')['address']
        except Exception as err:
            print(f"Failed to retrieve IP address for {NODE}: {err}")
            return None

def get_static_route(NODE):
    """Retrieves static routes from the specified node."""
    DEVICE = instantiate_node(NODE)
    if DEVICE:
        try:
            return DEVICE.api('staticroute').getall()
        except Exception as err:
            print(f"Failed to retrieve static routes for {NODE}: {err}")
            return None
    return None


def delete_static_route(NODE, DESTINATION, NEXT_HOP):
    """Deletes a static route from the specified node."""
    DEVICE = instantiate_node(NODE)
    if DEVICE:
        try:
            DEVICE.api('staticroute').delete(DESTINATION, NEXT_HOP)
            print(f"Deleted static route {DESTINATION, NEXT_HOP} from {NODE}")
        except Exception as err:
            print(f"Failed to delete static route {DESTINATION, NEXT_HOP} from {NODE}: {err}")

def create_interface(NODE, NAME, DESCRIPTION):
    """Creates a new interface on the specified node."""
    DEVICE = instantiate_node(NODE)
    if DEVICE:
        try:
            DEVICE.api('interfaces').set_description(NAME, value=DESCRIPTION)
            print(f"Created interface {NAME} on {NODE}")
        except Exception as err:
            print(f"Failed to create interface {NAME} on {NODE}: {err}")

for NODE in NODES:
    if NODE.startswith('leaf1') or NODE.startswith('leaf2'):
        create_interface(NODE, 'Ethernet1', '-> server1')
    elif NODE.startswith('leaf3') or NODE.startswith('leaf4'):
        create_interface(NODE, 'Ethernet1', '-> server2')
    elif NODE.startswith('leaf5') or NODE.startswith('leaf6'):
        create_interface(NODE, 'Ethernet1', '-> server3')
    
    DEVICE = instantiate_node(NODE)
    output = DEVICE.enable('show interfaces description')
    print(output[0]['result']['interfaceDescriptions']['Ethernet1']['description'])  # Print interface descriptions
    