from nornir_netmiko.tasks import netmiko_send_config

def fill(task):
    task.run(task=netmiko_send_config, config_commands=['int et1', 'isis metric 10'])
