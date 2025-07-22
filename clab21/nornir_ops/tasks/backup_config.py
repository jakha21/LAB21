from nornir_netmiko.tasks import netmiko_send_command

def backup_config(task):
    result = task.run(task=netmiko_send_command, command_string="show running-config")
    filename = f"backups/{task.host}.cfg"
    with open(filename, "w") as f:
        f.write(result.result)
