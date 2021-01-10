# How to clone

### Git > 2.13
```
git clone --recurse-submodules -j8 https://github.com/MilanDierickGD/GD_Data-and-more.git
cd GD_Data-and-more
```
### For already cloned repos, or older Git versions, use:
```
git clone https://github.com/MilanDierickGD/GD_Data-and-more.git
cd GD_Data-and-more
git submodule update --init --recursive
```
