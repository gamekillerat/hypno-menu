#include "stdafx.h"
#include "Discord.h"
#include "include/discord_rpc.h"
#include "include/discord_register.h"
#pragma comment(lib, "Discord/lib/discord-rpc.lib")

DiscordRichPresence discordPresence;
void UpdatePresence()
{
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.details = "HypnoV2";
	discordPresence.largeImageKey = "hypnologo";
	discordPresence.largeImageText = "HypnoV2";
	discordPresence.startTimestamp = time(0);
	Discord_UpdatePresence(&discordPresence);
}

void Initialize()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	Discord_Initialize("759100539513733150", &handlers, TRUE, nullptr);
}

void Shutdown()
{
	Discord_Shutdown();
}

void DiscordMain()
{
	Initialize();
	UpdatePresence();
}