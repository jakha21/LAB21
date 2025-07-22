from nornir_netmiko.tasks import netmiko_send_command

def task(task):
    return task.run(task=netmiko_send_command, command_string="show interfaces counters")
