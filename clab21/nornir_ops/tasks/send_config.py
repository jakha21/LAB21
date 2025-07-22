from nornir_netmiko.tasks import netmiko_send_config

def send_config(task, commands):
    task.run(task=netmiko_send_config, config_commands=commands)

