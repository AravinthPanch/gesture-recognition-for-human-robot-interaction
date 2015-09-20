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
LIB_DIR=$SOURCE_DIR/lib
DIST_DIR=$SOURCE_DIR/dist

NAO_HOST_NAME="nao5.local"
NAO_HOST_URL="nao@"$NAO_HOST_NAME
NAO_HOST_ROOT_URL="root@"$NAO_HOST_NAME
NAO_HOST_DIR="~/hri/"
NAO_HOST_SCP_URL=$NAO_HOST_URL":"$NAO_HOST_DIR

##############################################################

# Logger
log()
{
	local MSG=$(printf "[%s] %s" "$(date '+%d.%m.%Y %T')" "$1")
	printf "%s\n" "$MSG"
}

cleanup_hri()
{
	log "Cleaning up all the hri files on NAO"
	ssh $NAO_HOST_ROOT_URL "cd /usr/lib; \
		rm libstdc++.so libstdc++.so.6; \
		ln -s libstdc++.so.6.0.14 libstdc++.so; \
		ln -s libstdc++.so.6.0.14 libstdc++.so.6; \
		rm libstdc++.so.6.0.16; \
		rm -r /home/nao/hri; \
		rm /usr/local/lib/libNiTE2.so; \
		cd /etc/naoqi; \
		cp autoload.ini.orig autoload.ini; \
		/etc/init.d/naoqi restart"
}

apply_patch()
{
	ssh $NAO_HOST_ROOT_URL "cd /usr/lib; \
		chmod 755 libstdc++.so.6.0.16; \
		rm libstdc++.so libstdc++.so.6; \
		ln -s libstdc++.so.6.0.16 libstdc++.so; \
		ln -s libstdc++.so.6.0.16 libstdc++.so.6; \
		cd /etc/naoqi; \
		cp autoload.ini autoload.ini.orig; \
		cp /home/nao/hri/autoload.ini autoload.ini; \
		/etc/init.d/naoqi restart"
}

install_brain()
{
	log "Installing files to dist/ on local machine"
	cp "$CONFIG_DIR"/hri.json "$CONFIG_DIR"/signs.json $DIST_DIR
	cp "$PROJECT_DIR"/data/train/grt/hri-training-dataset.txt $DIST_DIR
}

update_variable()
{
	NAO_HOST_URL="nao@"$NAO_HOST_NAME
	NAO_HOST_SCP_URL=$NAO_HOST_URL":"$NAO_HOST_DIR
}

install_hri()
{
	update_variable
	ssh $NAO_HOST_URL "mkdir -p $NAO_HOST_DIR"

	log "Installing files onto $NAO_HOST_NAME"
	scp "$DIST_DIR"/human-robot-interaction-gentoo $NAO_HOST_SCP_URL/human-robot-interaction
	scp "$CONFIG_DIR"/hri.json "$CONFIG_DIR"/autoload.ini $NAO_HOST_SCP_URL

	log "Installing libraries onto $NAO_HOST_NAME"
	scp "$LIB_DIR"/NiTE2/libNiTE2-32.so $NAO_HOST_ROOT_URL":/usr/local/lib/libNiTE2.so"
	scp "$LIB_DIR"/LibStdC++/libstdc++.so.6.0.16 $NAO_HOST_ROOT_URL":/usr/lib/"

	log "Applying GLIBCXX Version Patch"
	apply_patch
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
# TODO: Also add scripts to start the setup
main()
{
	log "HRI Installer"
	log "Choose: 1-> Install on Robot \
		2-> Install on Localhost \
		3-> Cleanup on Robot"

	read ARGUMENT
	case "$ARGUMENT" in
		1)
			if is_host_available; then
				log "$NAO_HOST_NAME is available"
				install_hri
			else
				read -p "Enter the hostname of NAO:" NAO_HOST_NAME
				install_hri
			fi
			;;
		2)
			install_brain
			;;
		3)
			if is_host_available; then
				log "$NAO_HOST_NAME is available"
				cleanup_hri
			else
				read -p "Enter the hostname of NAO:" NAO_HOST_NAME
				cleanup_hri
			fi
			;;
		*)
			log "Choose: 1-> Install on Robot \
				2-> Install on Localhost \
				3-> Cleanup on Robot"
			exit 1
	esac

}

main
