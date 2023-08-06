# How to build a demo on your BlueOS

Add your ssh-key using:
```shell
ssh-copy-id -i ~/.ssh/id_rsa.pub pi@BlueOS_IP_Adress
```

Make sure that you have cmake or:
```shell
sudo apt-get install cmake
```

Then you can simply run the script!
```shell
./raspberry_build_run.sh
```

You can update the source directory with the last binaries:
Please check [releases](https://github.com/RaulTrombin/navigator-lib/releases/)