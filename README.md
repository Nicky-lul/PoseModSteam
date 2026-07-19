If you want install isntructions, scroll down to `# Installing`

# PoseModSteam

## ⚙️PoseMod

[PoseMod](https://mega.nz/folder/OFAiyZAL#jAmt_7c63A3Fwm60Pl_5fg/folder/iZgmmCjT/) is an easy-to-use drop-in ready mod for [Yandere Simulator](YandereSimulator.com).
It allows for you to move, customize, and pose characters within the game. It's mostly used for making video thumbnails, cheating to test theorys and myths with things like freecam and noclip, or making custom OCs to use in-game (probably the most difficult one).

## 🚄PoseModSteam

This is a non official modified edition of PoseMod3 that helps integrating the game with steam more.

By adding a non-steam game to steam (being `YandereSimulator.exe`) it will let you track your playtime (with client mods), take screenshots, and easily launch the game when in Big Picture mode.

This version of PoseMod was edited to instead of launch a specific instance, it will run the game through steam and inject the mod that way. In my mind, it's similar to the way [Unverum](https://gamebanana.com/tools/7162) or [tModLauncher](https://store.steampowered.com/app/1281930/tModLoader/) works.

Of course you can add this to your steam library as well as Yandere Simulator as non-steam games so you can play the non-modded version or the modded version with ease.

## ‼️DISCLAIMER

If you intend on only playing with a modded version of the gmae through steam, this is NOT for you. Just get the original PoseMod files [here](https://mega.nz/folder/OFAiyZAL#jAmt_7c63A3Fwm60Pl_5fg/folder/iZgmmCjT/), and add it to steam as a non-steam game.

# ⬇️ Installing

It's just like a normal installation of PoseMod:

1. Install the [latest release](https://github.com/Nicky-lul/PoseModSteam/releases/download/v1/PoseModSteam.zip).
2. Extract the .zip into a new folder.
3. Copy and paste the contents of this new folder into the Yandere Simulator directory.
4. Open Steam and add your `YandereSimulator.exe` as a new non-steam game (if you haven't already)
5. Press the little cog > Manage > Add desktop shortcut
6. Find your desktop shortcut and press properties.
7. Copy the numbers from the url. (Should look like "steam://rungameid/15125533231971041280")
8. find and open `steam_appid.txt` in your YandereSimulator directory.
9. Replace everything in it with your numbers. (Should **NOT** say "steam://rungameid/...", it should just be numbers.)
10. (*OPTIONAL, but better*) Add PoseModSteam64.exe as another non-steam game. 

# 🛣️ Journey

I have no clue why you're reading any further, but I guess here's the proccess I endured while making this..

I had yansim running through steam, and I wanted PoseMod, but encountered the issue where I wouldn't get playtime for Yansim when going through PoseMod, it would put that time on PoseMod instead of Yansim. So I got started by asking ChatGPT where to start with reverse engineering an exe, just because I wanted to make it launch through Steam and inject that intance instead of launching it's own instance.

ChatGPT had me install a few tools and we got started searching through decompiled binary. It was a hell of a mess, but we came to the conclusion (after 5 hours) that all it does is just injects a `pmmono64.dll` into a Yandere Simulator instance it ran. That's it. I was pissed to have wasted so much time finding this. ChatGPT had then been just as dumbfounded at this discovery and pretty much said "Right, then making our own .exe to launch this through steam should be easier than ever." and I installed Visual Studio and wrote this code for injecting the instance with PoseMod.
