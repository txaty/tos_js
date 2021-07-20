# TOS JS

## Simply Build Project and Flash Program on VS Code

- Install GNU ARM tool chain (2018 q2)
- Install OpenOCD
- Install VS Code Extension: [STM32 for VSCode](https://marketplace.visualstudio.com/items?itemName=bmd.stm32-for-vscode)
- Change the programmer to __STLink-v1__

## Add Shortcuts for Customized Tasks on VS Code

Open keybindings.json

Append following:

```json
{
    "key": "ctrl+shift+r",
    "command": "workbench.action.tasks.runTask",
    "args": "start"
},
{
    "key": "ctrl+shift+b",
    "command": "workbench.action.tasks.runTask",
    "args": "build"
}
```