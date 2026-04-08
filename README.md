# kiqkuk's Dotfiles

This repository serves as a personal vault for my **custom scripts and configurations**. It's a collection of experiments, late-night hacks, and spontaneous ideas.

**A fair warning**: This setup is highly personal. I made these because I felt like it, or just to see if I could. However, if a file exists in this repo, **I guarantee it works**.  
*(works on my machine, anyway. yours? probably not hahaha)*

## The Setup
Everything here is built with a **suckless** and **modular** mindset. Keeping things simple, minimal, and usable. I avoid long and complex scripts because **I often make typos**. Even with everything small and modular, **I still make typos sometimes**.

- **Shell:**  
Decoupled my bash config into env, completions, aliases, and prompt. They all meet in the main config file. Just make sure your **Bash can see the main config** and you're good.

- **Scripts:**  
Mostly status bar logic. If you use somebar or dwm, you'll know what to do with these. As long as they're **in your $PATH** you're set.

- **Patches:**  
My own tweaks for the suckless tools I use. ***I even added descriptions and comments to each patch.*** *(yeah, you're welcome)*

- **System:**  
System-level stuff. This is the personal zone, **highly tuned for my specific hardware** and workflow. **You probably won't need these**, but they are here for reference.

- **User:**  
Other configs that locate at `~/.config/`
