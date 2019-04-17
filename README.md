# lights
Connected my [LED string lights](https://www.amazon.com/s?k=led+string+lights&ref=nb_sb_noss_1) to the internet so I can control the brightness from my phone since getting out of bed is inconvenient. Keeping my code here so it doesn't get lost


### Physical circuit

**You will need:**
* **LED string lights** bought some on eBay, can also prob also find some on Amazon
* **WiFi Arduino board** The one I used is the ESP8266, just look up "WiFi board" on amazon. It's about $12 for a pack of 2.
* **MOSFET Transistor** to control the brightness

**Circuit diagram:**
<br>
<img src="circuitdiagram.png" width="600"/>
<br>
This was the best circuit diagram I could draw


### Installation
Clone repo
```
cd ~/
git clone https://github.com/andrewhu/lights.git
cd lights
```
Install dependencies
```
sudo apt-get update
sudo apt-get install python3 python3-venv
```
Setup virtual environment
```
python3 -m venv venv
. venv/bin/activate
pip install -r requirements.txt
```
Create systemd unit file
```
sudo cp _setup/lights.service /etc/systemd/system/
```
Start lights service
```
sudo systemctl start lights
```
Enable lights service on bootup
```
sudo systemctl enable lights
```
Nginx configuration
```
server {
    listen 5000;
    listen [::]:5000;

    server_name _;

    location / {
        include proxy_params;
        proxy_pass http://unix:/home/andrew/lights/lights.sock;
    }

}

```


