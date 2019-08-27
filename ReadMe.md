# NPP DirectWrite enabler

Enables DirectWrite for rendering in Scintilla. Needed to enable ligatures in fonts like [Fira Code](https://github.com/tonsky/FiraCode).

* [`SCI_SETTECHNOLOGY`](https://www.scintilla.org/ScintillaDoc.html#SCI_SETTECHNOLOGY) to SC_TECHNOLOGY_DIRECTWRITE
* [`SCI_SETBUFFEREDDRAW`](https://www.scintilla.org/ScintillaDoc.html#SCI_SETBUFFEREDDRAW) to 0


On Wine it [only results](https://bugs.winehq.org/show_bug.cgi?id=47690) into [extremily poor performance](https://bugs.winehq.org/show_bug.cgi?id=47689) currently.


