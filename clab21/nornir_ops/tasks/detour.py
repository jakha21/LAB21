from nornir_netmiko.tasks import netmiko_send_command, netmiko_send_config

def detour(task, intf=None):
    if not intf:
        return task.run(name="Missing interface", result="Please use --intf to specify the interface")

    # 1. Get current interface description
    cmd = f"show running-config interface {intf} | include description"
    result = task.run(task=netmiko_send_command, command_string=cmd)
    current_desc = result.result.strip()

    # 2. Parse and preserve existing description
    if "description" in current_desc:
        desc_text = current_desc.split("description", 1)[1].strip()
        if "DETOUR" not in desc_text:
            new_desc = f"description {desc_text} DETOUR"
        else:
            new_desc = f"description {desc_text}"  # Already has DETOUR
    else:
        new_desc = "description DETOUR"

    # 3. Build and send config
    commands = [
        f"interface {intf}",
        new_desc,
        "isis metric 16777214"
    ]
    return task.run(task=netmiko_send_config, name=f"Detour on {intf}", commands=commands)
