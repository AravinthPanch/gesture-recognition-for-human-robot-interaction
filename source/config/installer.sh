#!/bin/sh
##############################################################
#  Script     : installer.sh
#  Author     : Aravinth<me@aravinth.info>
#  Date       : 20/09/2015
##############################################################
# Description:
# - To install required files into NAO to run HRI
##############################################################

PROJECT_DIR="$(dirname $0)/../../"
CONFIG_DIR=$PROJECT_DIR/source/config
SOURCE_DIR=$PROJECT_DIR/source/human-robot-interaction
DIST_DIR=$SOURCE_DIR/dist

NAO_HOST_NAME="nao5.local"
NAO_HOST_URL="nao@"$NAO_HOST_NAME
NAO_HOST_DIR="~/hri/"
NAO_HOST_SCP_URL=$NAO_HOST_URL":"$NAO_HOST_DIR

##############################################################

# Logger
log()
{
	local MSG=$(printf "[%s] %s" "$(date '+%d.%m.%Y %T')" "$1")
	printf "%s\n" "$MSG"
}

update_variable()
{
	NAO_HOST_URL="nao@"$NAO_HOST_NAME
	NAO_HOST_DIR="~/hri/"
	NAO_HOST_SCP_URL=$NAO_HOST_URL":"$NAO_HOST_DIR
}

install_hri()
{
	update_variable
	log "Installing files onto $NAO_HOST_NAME"
	ssh $NAO_HOST_URL "mkdir -p $NAO_HOST_DIR"
	scp "$DIST_DIR"/human-robot-interaction-gentoo "$CONFIG_DIR"/hri.json $NAO_HOST_SCP_URL
}

is_host_available()
{
	local COUNT=$(ping -c 1 $NAO_HOST_NAME | grep icmp | wc -l)
	if [ $COUNT = 0 ]; then
		return 1
	else
		return 0
	fi
}

# Main Routine
main()
{
	log "HRI Installer"

	if is_host_available; then
		log "$NAO_HOST_NAME is available"
		install_hri
	else
		# Read NAO dns and install hri
		read -p "Enter the hostname of NAO:" NAO_HOST_NAME
		install_hri
	fi
}

main
