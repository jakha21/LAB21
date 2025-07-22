from nornir import InitNornir
from nornir_utils.plugins.functions import print_result
from tasks.send_config import send_config
from tasks.show_command import show_command
from tasks.backup_config import backup_config
from tasks.tap import tap
from tasks.fill import fill

# Initialize
nr = InitNornir(config_file="config.yaml")

# 1. Push config
#config_cmds = ["interface ma0", "description MGMT"]
#print("🔧 Sending Configurations")
#print_result(nr.run(task=send_config, commands=config_cmds))

# 2. Show command
print("📄 Capturing isis metric")
print_result(nr.run(task=show_command, command="sh isis interface ethernet 1 | i Metric"))

# 3. Backup configs
#print("💾 Backing up configurations")
#print_result(nr.run(task=backup_config))

# 4. Tap circuits
#print("Tapping circuit...")
#print_result(nr.run(task=tap))

# 5. Fill circuits
print("Filling circuits...")
print_result(nr.run(task=fill))
