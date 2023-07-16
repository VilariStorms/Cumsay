# Cumsay

A talking sperm that echos both standard and piped input.

Usage: cumsay <text_to_ejaculate>
Alternatively you can pipe input eg. `cat example.txt | cumsay --colour red`
```
Optional args:
  -h, --help     Show help message and exit
  -v, --version  Show version number and exit
  -c, --colour   Change the colour of the cum
  -r, --rainbow  Make the cum rainbow
```
## Install

Packages are available for the most popular distros but you can also build from source with:

```
user@femboy$ git clone https://github.com/VilariStorms/Cumsay.git && cd Cumsay
user@femboy$ make
```
You can then move `cumsay` to your desired directory or install with

```
user@femboy$ sudo make install
```
Uninstalling is as simple as:
```
user@femboy$ sudo make uninstall
```

For Debian and Debian based distros like Ubuntu, Mint, etc
```

# Download the GPG key
curl -sSL http://apt.vilari.site/cum/apt-repo/deriv-archive-keyring.pgp | gpg --dearmor | sudo tee /etc/apt/trusted.gpg.d/cumsay.gpg >/dev/null

# Add repository to the apt sources list
echo "deb http://apt.vilari.site/cum/apt-repo/ stable main" | sudo tee /etc/apt/sources.list.d/cumsay.list

# Update the apt package index
sudo apt-get update

# Install with apt
sudo apt install cumsay
```

For Arch based distros like Arch, Artix, etc
```
# Feel free to use your favorite AUR helper such as Pikaur instead
yay -S cumsay-bin
```

## Usage

```
vil@femboys.gay:~$ cumsay "I <3 cum!"
/‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒\  

             I <3 cum! 
 
\‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒/ 
                ____     _/ 
______     ___.'  o `.  / 
/~----,\___/,--.   ,_ | 
        `-----'   `---'  

```
You can also pipe input to cumsay ie: `cat example.txt | cumsay`

..and that's about it. If I'm bored enough, I might add something later.

### For windows

Save the following as install.ps1 and run with elevated permissions:
```
# Change the download url if neceessary
$url = "https://github.com/VilariStorms/Cumsay/releases/download/windows/cumsay.exe"
$downloadDirectory = "C:\cumsay"

# Create Cumsay Folder if it does not exists
if (-not (Test-Path -Path $downloadDirectory -PathType Container)) {
    New-Item -ItemType Directory -Force -Path $downloadDirectory
}
$exeFileName = "cumsay.exe"

# Add to path
$path = [System.Environment]::GetEnvironmentVariable("Path", [System.EnvironmentVariableTarget]::Machine)
Invoke-WebRequest -Uri $url -OutFile "$downloadDirectory\$exeFileName"

# Add the .exe file to the PATH environment variable
[System.Environment]::SetEnvironmentVariable("Path", "$path;$downloadDirectory", [System.EnvironmentVariableTarget]::Machine)

# Done
Write-Host "The $exeFileName file was downloaded and if ran with admin privilidges, was added to the PATH environment variable."
Write-Host "Please restart your terminal. You can now run cumsay from your commandline with cumsay <text-to-ejaculate>"
```


```

C:\CummyUser\cum> cumsay Cum on Windows!
/--------------------------------------\  

       Cum on Windows! 
 
\--------------------------------------/
                ____     _/
______     ___.'  o `.  /
/~----,\___/,--.   ,_ |
        `-----'   `---'
C:\CummyUser\cum> 
```

