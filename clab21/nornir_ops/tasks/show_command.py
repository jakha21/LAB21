from nornir_netmiko.tasks import netmiko_send_command

def show_command(task, command):
    result = task.run(task=netmiko_send_command, command_string=command)
    task.host["output"] = result.result #store for later use if needed
