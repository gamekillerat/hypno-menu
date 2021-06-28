#include "stdafx.h"

std::string prefix[3] = { "$", "%", "&" };
std::string commands[999] = { "godmode()", "weather(int)", "explosion(Vector3)", "moneyrain()", "stealth(int)" };
std::string hooks[999] = { "is_shooting(Player)", "localplayer()", "key(int)" };

std::string fp = "C:/Hypno/Metadata/Scripts/";
std::string last = ".txt";
std::string HypnoScript::file = "";
std::string script = fp + HypnoScript::file + last;

std::string sel_pl[] = { "@p", "@e", "@s" };
std::string tse_ev[] = { "KICK", "CEOKICK", "INVITE", "TELEPORT", "ERROR", "VEHICLEKICK", "ROTATE" };
std::string weather_id[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" };

std::string c_money = "moneyrain()";
std::string h_shooting = "is_shooting(";
std::string h_shooting2 = "is_shooting(" + sel_pl[1] + ")";
std::string h_shooting3 = "is_shooting(" + sel_pl[2] + ")";
std::string c_stealth = "stealth(";
std::string p_test = "test(";
std::string c_tse = "trigger_script_event(";
std::string c_weather = "set_weather(";
std::string c_kick = "kick(";
std::string c_error = "error(";
std::string c_tp = "teleport(";

int keyss[] = { VK_KEY_0, VK_KEY_1, VK_KEY_2, VK_KEY_3, VK_KEY_4, VK_KEY_5, VK_KEY_6, VK_KEY_7, VK_KEY_8, VK_KEY_9, VK_KEY_A, VK_KEY_B, VK_KEY_C, VK_KEY_D, VK_KEY_E, VK_KEY_F, VK_KEY_G, VK_KEY_H, VK_KEY_I, VK_KEY_J, VK_KEY_K, VK_KEY_L, VK_KEY_M, VK_KEY_N, VK_KEY_O, VK_KEY_P, VK_KEY_Q, VK_KEY_R, VK_KEY_S, VK_KEY_T, VK_KEY_U, VK_KEY_V, VK_KEY_W, VK_KEY_X, VK_KEY_Y, VK_KEY_Z };
std::string keycodes[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
std::string h_key = "key_pressed(+)";

bool HypnoScript::getFileContent(std::string fileName, std::vector<std::string> & vecOfStrs)
{

	// Open the File
	std::ifstream in(fileName.c_str());

	// Check if object is valid
	if (!in)
	{
		std::cerr << "Cannot open the File : " << fileName << std::endl;
		return false;
	}

	std::string str;
	// Read the next line from File untill it reaches the end.
	while (std::getline(in, str))
	{
		// Line contains string of length > 0 then save it in vector
		if (str.size() > 0)
			vecOfStrs.push_back(str);
	}
	//Close The File
	in.close();
	return true;
}

int HypnoScript::getLines(std::string f) {
	return Features::countLines(f);
}

std::string HypnoScript::readLine(std::string f, int n) {
	return Features::readLine(f, n);
}

bool HypnoScript::checkCommand(std::string cmd, int line) 
{
	if (readLine(script, line) == cmd) {
		return true;
	}
	else {
		return false;
	}
}

void HypnoScript::executeCommand(int line, std::string cmd, std::function<void()> function) {
	if (readLine(script, line) == cmd) {
		function();
	}
}

void HypnoScript::hookCommand(bool condition, std::string thiscmd, std::string cmd, std::function<void()> function) {
	int lineFound = 0;
	for (int i = 0; i < getLines(script); i++) {
		if (checkCommand(prefix[0] + thiscmd, i) && condition) {
			lineFound = i;
			executeCommand(lineFound + 1, prefix[1] + cmd, function);
		}
	}
}

void HypnoScript::normalCommand(std::string thiscmd, std::function<void()> function) {
	int lineFound = 0;
	for (int i = 0; i < getLines(script); i++) {
		if (checkCommand(prefix[2] + thiscmd, i)) {
			lineFound = i;
			function();
		}
	}
}
int HypnoScript::font = 0;
int HypnoScript::fontselector = 0;

std::string HypnoScript::getParam(std::string cmd) {
	for (int i = 0; i < getLines(script); i++) {
		if (checkCommand(prefix[2] + cmd, i)) {
			//TO DO: do it!
		}
	}
	return "";
}

enum eHudColor
{
	HUD_COLOUR_PURE_WHITE,
	HUD_COLOUR_WHITE,
	HUD_COLOUR_BLACK,
	HUD_COLOUR_GREY,
	HUD_COLOUR_GREYLIGHT,
	HUD_COLOUR_GREYDARK,
	HUD_COLOUR_RED,
	HUD_COLOUR_REDLIGHT,
	HUD_COLOUR_REDDARK,
	HUD_COLOUR_BLUE,
	HUD_COLOUR_BLUELIGHT,
	HUD_COLOUR_BLUEDARK,
	HUD_COLOUR_YELLOW,
	HUD_COLOUR_YELLOWLIGHT,
	HUD_COLOUR_YELLOWDARK,
	HUD_COLOUR_ORANGE,
	HUD_COLOUR_ORANGELIGHT,
	HUD_COLOUR_ORANGEDARK,
	HUD_COLOUR_GREEN,
	HUD_COLOUR_GREENLIGHT,
	HUD_COLOUR_GREENDARK,
	HUD_COLOUR_PURPLE,
	HUD_COLOUR_PURPLELIGHT,
	HUD_COLOUR_PURPLEDARK,
	HUD_COLOUR_PINK,
	HUD_COLOUR_RADAR_HEALTH,
	HUD_COLOUR_RADAR_ARMOUR,
	HUD_COLOUR_RADAR_DAMAGE,
	HUD_COLOUR_NET_PLAYER1,
	HUD_COLOUR_NET_PLAYER2,
	HUD_COLOUR_NET_PLAYER3,
	HUD_COLOUR_NET_PLAYER4,
	HUD_COLOUR_NET_PLAYER5,
	HUD_COLOUR_NET_PLAYER6,
	HUD_COLOUR_NET_PLAYER7,
	HUD_COLOUR_NET_PLAYER8,
	HUD_COLOUR_NET_PLAYER9,
	HUD_COLOUR_NET_PLAYER10,
	HUD_COLOUR_NET_PLAYER11,
	HUD_COLOUR_NET_PLAYER12,
	HUD_COLOUR_NET_PLAYER13,
	HUD_COLOUR_NET_PLAYER14,
	HUD_COLOUR_NET_PLAYER15,
	HUD_COLOUR_NET_PLAYER16,
	HUD_COLOUR_NET_PLAYER17,
	HUD_COLOUR_NET_PLAYER18,
	HUD_COLOUR_NET_PLAYER19,
	HUD_COLOUR_NET_PLAYER20,
	HUD_COLOUR_NET_PLAYER21,
	HUD_COLOUR_NET_PLAYER22,
	HUD_COLOUR_NET_PLAYER23,
	HUD_COLOUR_NET_PLAYER24,
	HUD_COLOUR_NET_PLAYER25,
	HUD_COLOUR_NET_PLAYER26,
	HUD_COLOUR_NET_PLAYER27,
	HUD_COLOUR_NET_PLAYER28,
	HUD_COLOUR_NET_PLAYER29,
	HUD_COLOUR_NET_PLAYER30,
	HUD_COLOUR_NET_PLAYER31,
	HUD_COLOUR_NET_PLAYER32,
	HUD_COLOUR_SIMPLEBLIP_DEFAULT,
	HUD_COLOUR_MENU_BLUE,
	HUD_COLOUR_MENU_GREY_LIGHT,
	HUD_COLOUR_MENU_BLUE_EXTRA_DARK,
	HUD_COLOUR_MENU_YELLOW,
	HUD_COLOUR_MENU_YELLOW_DARK,
	HUD_COLOUR_MENU_GREEN,
	HUD_COLOUR_MENU_GREY,
	HUD_COLOUR_MENU_GREY_DARK,
	HUD_COLOUR_MENU_HIGHLIGHT,
	HUD_COLOUR_MENU_STANDARD,
	HUD_COLOUR_MENU_DIMMED,
	HUD_COLOUR_MENU_EXTRA_DIMMED,
	HUD_COLOUR_BRIEF_TITLE,
	HUD_COLOUR_MID_GREY_MP,
	HUD_COLOUR_NET_PLAYER1_DARK,
	HUD_COLOUR_NET_PLAYER2_DARK,
	HUD_COLOUR_NET_PLAYER3_DARK,
	HUD_COLOUR_NET_PLAYER4_DARK,
	HUD_COLOUR_NET_PLAYER5_DARK,
	HUD_COLOUR_NET_PLAYER6_DARK,
	HUD_COLOUR_NET_PLAYER7_DARK,
	HUD_COLOUR_NET_PLAYER8_DARK,
	HUD_COLOUR_NET_PLAYER9_DARK,
	HUD_COLOUR_NET_PLAYER10_DARK,
	HUD_COLOUR_NET_PLAYER11_DARK,
	HUD_COLOUR_NET_PLAYER12_DARK,
	HUD_COLOUR_NET_PLAYER13_DARK,
	HUD_COLOUR_NET_PLAYER14_DARK,
	HUD_COLOUR_NET_PLAYER15_DARK,
	HUD_COLOUR_NET_PLAYER16_DARK,
	HUD_COLOUR_NET_PLAYER17_DARK,
	HUD_COLOUR_NET_PLAYER18_DARK,
	HUD_COLOUR_NET_PLAYER19_DARK,
	HUD_COLOUR_NET_PLAYER20_DARK,
	HUD_COLOUR_NET_PLAYER21_DARK,
	HUD_COLOUR_NET_PLAYER22_DARK,
	HUD_COLOUR_NET_PLAYER23_DARK,
	HUD_COLOUR_NET_PLAYER24_DARK,
	HUD_COLOUR_NET_PLAYER25_DARK,
	HUD_COLOUR_NET_PLAYER26_DARK,
	HUD_COLOUR_NET_PLAYER27_DARK,
	HUD_COLOUR_NET_PLAYER28_DARK,
	HUD_COLOUR_NET_PLAYER29_DARK,
	HUD_COLOUR_NET_PLAYER30_DARK,
	HUD_COLOUR_NET_PLAYER31_DARK,
	HUD_COLOUR_NET_PLAYER32_DARK,
	HUD_COLOUR_BRONZE,
	HUD_COLOUR_SILVER,
	HUD_COLOUR_GOLD,
	HUD_COLOUR_PLATINUM,
	HUD_COLOUR_GANG1,
	HUD_COLOUR_GANG2,
	HUD_COLOUR_GANG3,
	HUD_COLOUR_GANG4,
	HUD_COLOUR_SAME_CREW,
	HUD_COLOUR_FREEMODE,
	HUD_COLOUR_PAUSE_BG,
	HUD_COLOUR_FRIENDLY,
	HUD_COLOUR_ENEMY,
	HUD_COLOUR_LOCATION,
	HUD_COLOUR_PICKUP,
	HUD_COLOUR_PAUSE_SINGLEPLAYER,
	HUD_COLOUR_FREEMODE_DARK,
	HUD_COLOUR_INACTIVE_MISSION,
	HUD_COLOUR_DAMAGE,
	HUD_COLOUR_PINKLIGHT,
	HUD_COLOUR_PM_MITEM_HIGHLIGHT,
	HUD_COLOUR_SCRIPT_VARIABLE,
	HUD_COLOUR_YOGA,
	HUD_COLOUR_TENNIS,
	HUD_COLOUR_GOLF,
	HUD_COLOUR_SHOOTING_RANGE,
	HUD_COLOUR_FLIGHT_SCHOOL,
	HUD_COLOUR_NORTH_BLUE,
	HUD_COLOUR_SOCIAL_CLUB,
	HUD_COLOUR_PLATFORM_BLUE,
	HUD_COLOUR_PLATFORM_GREEN,
	HUD_COLOUR_PLATFORM_GREY,
	HUD_COLOUR_FACEBOOK_BLUE,
	HUD_COLOUR_INGAME_BG,
	HUD_COLOUR_DARTS,
	HUD_COLOUR_WAYPOINT,
	HUD_COLOUR_MICHAEL,
	HUD_COLOUR_FRANKLIN,
	HUD_COLOUR_TREVOR,
	HUD_COLOUR_GOLF_P1,
	HUD_COLOUR_GOLF_P2,
	HUD_COLOUR_GOLF_P3,
	HUD_COLOUR_GOLF_P4,
	HUD_COLOUR_WAYPOINTLIGHT,
	HUD_COLOUR_WAYPOINTDARK,
	HUD_COLOUR_PANEL_LIGHT,
	HUD_COLOUR_MICHAEL_DARK,
	HUD_COLOUR_FRANKLIN_DARK,
	HUD_COLOUR_TREVOR_DARK,
	HUD_COLOUR_OBJECTIVE_ROUTE,
	HUD_COLOUR_PAUSEMAP_TINT,
	HUD_COLOUR_PAUSE_DESELECT,
	HUD_COLOUR_PM_WEAPONS_PURCHASABLE,
	HUD_COLOUR_PM_WEAPONS_LOCKED,
	HUD_COLOUR_END_SCREEN_BG,
	HUD_COLOUR_CHOP,
	HUD_COLOUR_PAUSEMAP_TINT_HALF,
	HUD_COLOUR_NORTH_BLUE_OFFICIAL,
	HUD_COLOUR_SCRIPT_VARIABLE_2,
	HUD_COLOUR_H,
	HUD_COLOUR_HDARK,
	HUD_COLOUR_T,
	HUD_COLOUR_TDARK,
	HUD_COLOUR_HSHARD,
	HUD_COLOUR_CONTROLLER_MICHAEL,
	HUD_COLOUR_CONTROLLER_FRANKLIN,
	HUD_COLOUR_CONTROLLER_TREVOR,
	HUD_COLOUR_CONTROLLER_CHOP,
	HUD_COLOUR_VIDEO_EDITOR_VIDEO,
	HUD_COLOUR_VIDEO_EDITOR_AUDIO,
	HUD_COLOUR_VIDEO_EDITOR_TEXT,
	HUD_COLOUR_HB_BLUE,
	HUD_COLOUR_HB_YELLOW,
	HUD_COLOUR_VIDEO_EDITOR_SCORE,
	HUD_COLOUR_VIDEO_EDITOR_AUDIO_FADEOUT,
	HUD_COLOUR_VIDEO_EDITOR_TEXT_FADEOUT,
	HUD_COLOUR_VIDEO_EDITOR_SCORE_FADEOUT,
	HUD_COLOUR_HEIST_BACKGROUND,
	HUD_COLOUR_VIDEO_EDITOR_AMBIENT,
	HUD_COLOUR_VIDEO_EDITOR_AMBIENT_FADEOUT,
	HUD_COLOUR_GB,
	HUD_COLOUR_G,
	HUD_COLOUR_B,
	HUD_COLOUR_LOW_FLOW,
	HUD_COLOUR_LOW_FLOW_DARK,
	HUD_COLOUR_G1,
	HUD_COLOUR_G2,
	HUD_COLOUR_G3,
	HUD_COLOUR_G4,
	HUD_COLOUR_G5,
	HUD_COLOUR_G6,
	HUD_COLOUR_G7,
	HUD_COLOUR_G8,
	HUD_COLOUR_G9,
	HUD_COLOUR_G10,
	HUD_COLOUR_G11,
	HUD_COLOUR_G12,
	HUD_COLOUR_G13,
	HUD_COLOUR_G14,
	HUD_COLOUR_G15,
	HUD_COLOUR_ADVERSARY,
	HUD_COLOUR_DEGEN_RED,
	HUD_COLOUR_DEGEN_YELLOW,
	HUD_COLOUR_DEGEN_GREEN,
	HUD_COLOUR_DEGEN_CYAN,
	HUD_COLOUR_DEGEN_BLUE,
	HUD_COLOUR_DEGEN_MAGENTA,
	HUD_COLOUR_STUNT_1,
	HUD_COLOUR_STUNT_2
};

void HypnoScript::HudColourChange() 
{
	UI::_SET_HUD_COLOUR(HUD_COLOUR_FREEMODE, Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, 255);
	UI::_SET_HUD_COLOUR(HUD_COLOUR_MICHAEL,  Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, 255);
	UI::_SET_HUD_COLOUR(HUD_COLOUR_FRANKLIN, Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, 255);
	UI::_SET_HUD_COLOUR(HUD_COLOUR_TREVOR,   Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, 255);
	UI::_SET_HUD_COLOUR(HUD_COLOUR_WAYPOINT, Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, 255);
}

void HypnoScript::keypressed(int key, std::string key2) {
	bool b00l = GetAsyncKeyState(key);
	hookCommand(b00l, h_key, c_money, [] { Features::customDropBool2 = !Features::customDropBool2; });
	hookCommand(b00l, h_key, c_stealth, [] {});
	std::string params[10] = { "10000000", "9000000", "8000000", "7000000", "6000000", "5000000", "4000000", "3000000", "2000000", "1000000" };
	for (int i = 0; i < ARRAYSIZE(params); i++) {
		hookCommand(b00l, h_key, c_stealth + params[i] + ")", [i] { std::string params2[10] = { "10000000", "9000000", "8000000", "7000000", "6000000", "5000000", "4000000", "3000000", "2000000", "1000000" }; Any var0 = INT_MAX; UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, 312105838, 1445302971, stoi(params2[i]), 4); UNK3::_NETWORK_SHOP_CHECKOUT_START(var0); });
	}
	/*for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		for (int j = 0; j < ARRAYSIZE(tse_ev); j++) {
			hookCommand(b00l, h_shooting, c_tse + sel_pl[i] + ", " + tse_ev[j] + ")", [i, j] { cmdSE(i, j); });
		}
	}*/
	for (int i = 0; i < ARRAYSIZE(weather_id); i++) {
		hookCommand(b00l, h_key, c_weather + weather_id[i] + ")", [i] { Hooking::set_session_weather(1, stoi(weather_id[i]), 76, 0); });
	}
	for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		hookCommand(b00l, h_key, c_kick + sel_pl[i] + ")", [i] {
			if (i == 0) {
				unsigned int Bit = (1 << PLAYER::PLAYER_ID());
				uint64_t args[3] = { -120668417, PLAYER::PLAYER_PED_ID(), 48 };
				Hooking::trigger_script_event(1, args, 3, Bit);
			}
			else if (i == 1) {
				for (int i = 0; i < 33; i++) {
					unsigned int Bit = (1 << i);
					uint64_t args[3] = { -120668417, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 48 };
					Hooking::trigger_script_event(1, args, 3, Bit);
				}
			}
			else {
				unsigned int Bit = (1 << Features::Online::selectedPlayer);
				uint64_t args[3] = { -120668417, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 48 };
				Hooking::trigger_script_event(1, args, 3, Bit);
			}
		});
	}
	for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		hookCommand(b00l, h_key, c_tp + sel_pl[i] + ")", [i] {
			if (i == 0) {
				unsigned int Bit = (1 << PLAYER::PLAYER_ID());
				uint64_t args[9] = { 1000837481, PLAYER::PLAYER_PED_ID(), 0, -1, 1, 1, 0, 0, 0 };
				Hooking::trigger_script_event(1, args, 9, Bit);
			}
			else if (i == 1) {
				for (int i = 0; i < 33; i++) {
					unsigned int Bit = (1 << i);
					uint64_t args[9] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0, -1, 1, 1, 0, 0, 0 };
					Hooking::trigger_script_event(1, args, 9, Bit);
				}
			}
			else {
				unsigned int Bit = (1 << Features::Online::selectedPlayer);
				uint64_t args[9] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0, -1, 1, 1, 0, 0, 0 };
				Hooking::trigger_script_event(1, args, 9, Bit);
			}
		});
	}
	for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		hookCommand(b00l, h_key, c_error + sel_pl[i] + ")", [i] {
			if (i == 0) {
				unsigned int Bit = (1 << PLAYER::PLAYER_ID());
				auto var0 = globalHandle(1625435 + 1 + PLAYER::PLAYER_ID() * 560 + 491).As<std::uint64_t>();
				auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
				uint64_t args[8] = { 1000837481, PLAYER::PLAYER_PED_ID(), 10000, 0, 0, var0, var1, var1 };
				Hooking::trigger_script_event(1, args, 8, Bit);
			}
			else if (i == 1) {
				for (int i = 0; i < 33; i++) {
					unsigned int Bit = (1 << i);
					auto var0 = globalHandle(1625435 + 1 + i * 560 + 491).As<std::uint64_t>();
					auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
					uint64_t args[8] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 10000, 0, 0, var0, var1, var1 };
					Hooking::trigger_script_event(1, args, 8, Bit);
				}
			}
			else {
				unsigned int Bit = (1 << Features::Online::selectedPlayer);
				auto var0 = globalHandle(1625435 + 1 + Features::Online::selectedPlayer * 560 + 491).As<std::uint64_t>();
				auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
				uint64_t args[8] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 10000, 0, 0, var0, var1, var1 };
				Hooking::trigger_script_event(1, args, 8, Bit);
			}
		});
	}
}

void HypnoScript::shooting1(std::string mode) {
	Player ppp;
	if (mode == sel_pl[0]) {
		ppp = PLAYER::PLAYER_PED_ID();
	}
	else if (mode == sel_pl[1]) {
		for (int lmao = 0; lmao < 33; lmao++) {
			ppp = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(lmao);
		}
	}
	else if (mode == sel_pl[2]) {
		ppp = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
	}
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(ppp, 1);
	bool b00l = PED::IS_PED_SHOOTING_IN_AREA(ppp, coords.x, coords.y, coords.z, coords.x, coords.y, coords.z, true, true);
	hookCommand(b00l, h_shooting + mode + ")", c_money, [] { Features::customDropBool2 = !Features::customDropBool2; });
	hookCommand(b00l, h_shooting + mode + ")", c_stealth, [] {});
	std::string params[10] = { "10000000", "9000000", "8000000", "7000000", "6000000", "5000000", "4000000", "3000000", "2000000", "1000000" };
	for (int i = 0; i < ARRAYSIZE(params); i++) {
		hookCommand(b00l, h_shooting + mode + ")", c_stealth + params[i] + ")", [i] { std::string params2[10] = { "10000000", "9000000", "8000000", "7000000", "6000000", "5000000", "4000000", "3000000", "2000000", "1000000" }; Any var0 = INT_MAX; UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, 312105838, 1445302971, stoi(params2[i]), 4); UNK3::_NETWORK_SHOP_CHECKOUT_START(var0); });
	}
	/*for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		for (int j = 0; j < ARRAYSIZE(tse_ev); j++) {
			hookCommand(b00l, h_shooting, c_tse + sel_pl[i] + ", " + tse_ev[j] + ")", [i, j] { cmdSE(i, j); });
		}
	}*/
	for (int i = 0; i < ARRAYSIZE(weather_id); i++) {
		hookCommand(b00l, h_shooting + mode + ")", c_weather + weather_id[i] + ")", [i] { Hooking::set_session_weather(1, stoi(weather_id[i]), 76, 0); });
	}
	for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		hookCommand(b00l, h_shooting + mode + ")", c_kick + sel_pl[i] + ")", [i] {
			if (i == 0) {
				unsigned int Bit = (1 << PLAYER::PLAYER_ID());
				uint64_t args[3] = { -120668417, PLAYER::PLAYER_PED_ID(), 48 };
				Hooking::trigger_script_event(1, args, 3, Bit);
			}
			else if (i == 1) {
				for (int i = 0; i < 33; i++) {
					unsigned int Bit = (1 << i);
					uint64_t args[3] = { -120668417, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 48 };
					Hooking::trigger_script_event(1, args, 3, Bit);
				}
			}
			else {
				unsigned int Bit = (1 << Features::Online::selectedPlayer);
				uint64_t args[3] = { -120668417, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 48 };
				Hooking::trigger_script_event(1, args, 3, Bit);
			}
		});
	}
	for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		hookCommand(b00l, h_shooting + mode + ")", c_tp + sel_pl[i] + ")", [i] {
			if (i == 0) {
				unsigned int Bit = (1 << PLAYER::PLAYER_ID());
				uint64_t args[9] = { 1000837481, PLAYER::PLAYER_PED_ID(), 0, -1, 1, 1, 0, 0, 0 };
				Hooking::trigger_script_event(1, args, 9, Bit);
			}
			else if (i == 1) {
				for (int i = 0; i < 33; i++) {
					unsigned int Bit = (1 << i);
					uint64_t args[9] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0, -1, 1, 1, 0, 0, 0 };
					Hooking::trigger_script_event(1, args, 9, Bit);
				}
			}
			else {
				unsigned int Bit = (1 << Features::Online::selectedPlayer);
				uint64_t args[9] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0, -1, 1, 1, 0, 0, 0 };
				Hooking::trigger_script_event(1, args, 9, Bit);
			}
		});
	}
	for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		hookCommand(b00l, h_shooting + mode + ")", c_error + sel_pl[i] + ")", [i] {
			if (i == 0) {
				unsigned int Bit = (1 << PLAYER::PLAYER_ID());
				auto var0 = globalHandle(1625435 + 1 + PLAYER::PLAYER_ID() * 560 + 491).As<std::uint64_t>();
				auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
				uint64_t args[8] = { 1000837481, PLAYER::PLAYER_PED_ID(), 10000, 0, 0, var0, var1, var1 };
				Hooking::trigger_script_event(1, args, 8, Bit);
			}
			else if (i == 1) {
				for (int i = 0; i < 33; i++) {
					unsigned int Bit = (1 << i);
					auto var0 = globalHandle(1625435 + 1 + i * 560 + 491).As<std::uint64_t>();
					auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
					uint64_t args[8] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 10000, 0, 0, var0, var1, var1 };
					Hooking::trigger_script_event(1, args, 8, Bit);
				}
			}
			else {
				unsigned int Bit = (1 << Features::Online::selectedPlayer);
				auto var0 = globalHandle(1625435 + 1 + Features::Online::selectedPlayer * 560 + 491).As<std::uint64_t>();
				auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
				uint64_t args[8] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 10000, 0, 0, var0, var1, var1 };
				Hooking::trigger_script_event(1, args, 8, Bit);
			}
		});
	}
}

void HypnoScript::moneydrop() {
	normalCommand(c_money, [] { Features::customDropBool2 = !Features::customDropBool2; });
}

void HypnoScript::stealth() {
	std::string params[10] = { "10000000", "9000000", "8000000", "7000000", "6000000", "5000000", "4000000", "3000000", "2000000", "1000000" };
	for (int i = 0; i < ARRAYSIZE(params); i++) {
		normalCommand(c_stealth + params[i] + ")", [i] { std::string params2[10] = { "10000000", "9000000", "8000000", "7000000", "6000000", "5000000", "4000000", "3000000", "2000000", "1000000" }; Any var0 = INT_MAX; UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, 312105838, 1445302971, stoi(params2[i]), 4); UNK3::_NETWORK_SHOP_CHECKOUT_START(var0); });
	}
}

void HypnoScript::cmdSE(int playermode, int id) {
	unsigned int Bit;
	Player ply;
	Player pl2;
	if (playermode == 0) {
		ply = PLAYER::PLAYER_PED_ID();
		pl2 = PLAYER::PLAYER_ID();
		Bit = (1 << pl2);	
		uint64_t* args;
		if (id == 0) {
			args[0] = -120668417;
			args[1] = ply;
			args[2] = 48;
			Hooking::trigger_script_event(1, args, 3, Bit);
		}
		else if (id == 1) {
			args[0] = -1190833098;
			args[1] = ply;
			args[2] = 0;
			args[3] = 6;
			Hooking::trigger_script_event(1, args, 4, Bit);
		}
		else if (id == 2) {
			args[0] = 4119492672;
			args[1] = ply;
			args[2] = 0;
			args[3] = 1;
			Hooking::trigger_script_event(1, args, 4, Bit);
		}
		else if (id == 3) {
			args[0] = 1000837481;
			args[1] = ply;
			args[2] = 0;
			args[3] = -1;
			args[4] = 1;
			args[5] = 1;
			args[6] = 0;
			args[7] = 0;
			args[8] = 0;
			Hooking::trigger_script_event(1, args, 9, Bit);
		}
		else if (id == 4) {
			auto var0 = globalHandle(1625435 + 1 + pl2 * 560 + 491).As<std::uint64_t>();
			auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
			args[0] = -1920290846;
			args[1] = ply;
			args[2] = 10000;
			args[3] = 0;
			args[4] = 0;
			args[5] = var0;
			args[6] = var1;
			args[7] = var1;
			Hooking::trigger_script_event(1, args, 8, Bit);
		}
		else if (id == 5) {
			args[0] = 713068249;
			args[1] = ply;
			args[2] = -1432462772;
			args[3] = 1000000;
			Hooking::trigger_script_event(1, args, 4, Bit);
		}
		else if (id == 6) {
			args[0] = 325218053;
			args[1] = ply;
			Hooking::trigger_script_event(1, args, 2, Bit);
		}
		else if (id == 7) {
			args[0] = 566035618;
			args[1] = ply;
			args[2] = -1432407380;
			Hooking::trigger_script_event(1, args, 3, Bit);
		}
	}
	else if (playermode == 1) {
		for (int lmao = 0; lmao < 33; lmao++) {
			ply = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(lmao);
			pl2 = lmao;
			Bit = (1 << pl2);
			uint64_t* args;
			if (id == 0) {
				args[0] = -120668417;
				args[1] = ply;
				args[2] = 48;
				Hooking::trigger_script_event(1, args, 3, Bit);
			}
			else if (id == 1) {
				args[0] = -1190833098;
				args[1] = ply;
				args[2] = 0;
				args[3] = 6;
				Hooking::trigger_script_event(1, args, 4, Bit);
			}
			else if (id == 2) {
				args[0] = 4119492672;
				args[1] = ply;
				args[2] = 0;
				args[3] = 1;
				Hooking::trigger_script_event(1, args, 4, Bit);
			}
			else if (id == 3) {
				args[0] = 1000837481;
				args[1] = ply;
				args[2] = 0;
				args[3] = -1;
				args[4] = 1;
				args[5] = 1;
				args[6] = 0;
				args[7] = 0;
				args[8] = 0;
				Hooking::trigger_script_event(1, args, 9, Bit);
			}
			else if (id == 4) {
				auto var0 = globalHandle(1625435 + 1 + pl2 * 560 + 491).As<std::uint64_t>();
				auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
				args[0] = -1920290846;
				args[1] = ply;
				args[2] = 10000;
				args[3] = 0;
				args[4] = 0;
				args[5] = var0;
				args[6] = var1;
				args[7] = var1;
				Hooking::trigger_script_event(1, args, 8, Bit);
			}
			else if (id == 5) {
				args[0] = 713068249;
				args[1] = ply;
				args[2] = -1432462772;
				args[3] = 1000000;
				Hooking::trigger_script_event(1, args, 4, Bit);
			}
			else if (id == 6) {
				args[0] = 325218053;
				args[1] = ply;
				Hooking::trigger_script_event(1, args, 2, Bit);
			}
			else if (id == 7) {
				args[0] = 566035618;
				args[1] = ply;
				args[2] = -1432407380;
				Hooking::trigger_script_event(1, args, 3, Bit);
			}
		}
	}
	else if (playermode == 2) {
		ply = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
		pl2 = Features::Online::selectedPlayer;
		Bit = (1 << pl2);
		uint64_t* args;
		if (id == 0) {
			args[0] = -120668417;
			args[1] = ply;
			args[2] = 48;
			Hooking::trigger_script_event(1, args, 3, Bit);
		}
		else if (id == 1) {
			args[0] = -1190833098;
			args[1] = ply;
			args[2] = 0;
			args[3] = 6;
			Hooking::trigger_script_event(1, args, 4, Bit);
		}
		else if (id == 2) {
			args[0] = 4119492672;
			args[1] = ply;
			args[2] = 0;
			args[3] = 1;
			Hooking::trigger_script_event(1, args, 4, Bit);
		}
		else if (id == 3) {
			args[0] = 1000837481;
			args[1] = ply;
			args[2] = 0;
			args[3] = -1;
			args[4] = 1;
			args[5] = 1;
			args[6] = 0;
			args[7] = 0;
			args[8] = 0;
			Hooking::trigger_script_event(1, args, 9, Bit);
		}
		else if (id == 4) {
			auto var0 = globalHandle(1625435 + 1 + pl2 * 560 + 491).As<std::uint64_t>();
			auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
			args[0] = -1920290846;
			args[1] = ply;
			args[2] = 10000;
			args[3] = 0;
			args[4] = 0;
			args[5] = var0;
			args[6] = var1;
			args[7] = var1;
			Hooking::trigger_script_event(1, args, 8, Bit);
		}
		else if (id == 5) {
			args[0] = 713068249;
			args[1] = ply;
			args[2] = -1432462772;
			args[3] = 1000000;
			Hooking::trigger_script_event(1, args, 4, Bit);
		}
		else if (id == 6) {
			args[0] = 325218053;
			args[1] = ply;
			Hooking::trigger_script_event(1, args, 2, Bit);
		}
		else if (id == 7) {
			args[0] = 566035618;
			args[1] = ply;
			args[2] = -1432407380;
			Hooking::trigger_script_event(1, args, 3, Bit);
		}
	}
}

void HypnoScript::tse() {
	for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		for(int j = 0; j < ARRAYSIZE(tse_ev); j++){
			normalCommand(c_tse + sel_pl[i] + ", " + tse_ev[j] + ")", [i, j] { cmdSE(i, j); });
		}
	}
}

void HypnoScript::weather() {
	for (int i = 0; i < ARRAYSIZE(weather_id); i++) {
		normalCommand(c_weather + weather_id[i] + ")", [i] { Hooking::set_session_weather(1, stoi(weather_id[i]), 76, 0); });
	}
}

void HypnoScript::kick() {
	for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		normalCommand(c_kick + sel_pl[i] + ")", [i] {
			if (i == 0) {
				unsigned int Bit = (1 << PLAYER::PLAYER_ID());
				uint64_t args[3] = { -120668417, PLAYER::PLAYER_PED_ID(), 48 };
				Hooking::trigger_script_event(1, args, 3, Bit);
			}
			else if (i == 1) {
				for (int i = 0; i < 33; i++) {
					unsigned int Bit = (1 << i);
					uint64_t args[3] = { -120668417, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 48 };
					Hooking::trigger_script_event(1, args, 3, Bit);
				}
			}
			else {
				unsigned int Bit = (1 << Features::Online::selectedPlayer);
				uint64_t args[3] = { -120668417, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 48 };
				Hooking::trigger_script_event(1, args, 3, Bit);
			}
		});
	}
}

void HypnoScript::tp() {
	for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		normalCommand(c_tp + sel_pl[i] + ")", [i] {
			if (i == 0) {
				unsigned int Bit = (1 << PLAYER::PLAYER_ID());
				uint64_t args[9] = { 1000837481, PLAYER::PLAYER_PED_ID(), 0, -1, 1, 1, 0, 0, 0 };
				Hooking::trigger_script_event(1, args, 9, Bit);
			}
			else if (i == 1) {
				for (int i = 0; i < 33; i++) {
					unsigned int Bit = (1 << i);
					uint64_t args[9] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0, -1, 1, 1, 0, 0, 0 };
					Hooking::trigger_script_event(1, args, 9, Bit);
				}
			}
			else {
				unsigned int Bit = (1 << Features::Online::selectedPlayer);
				uint64_t args[9] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 0, -1, 1, 1, 0, 0, 0 };
				Hooking::trigger_script_event(1, args, 9, Bit);
			}
		});
	}
}

void HypnoScript::transaction() {
	for (int i = 0; i < ARRAYSIZE(sel_pl); i++) {
		normalCommand(c_error + sel_pl[i] + ")", [i] {
			if (i == 0) {
				unsigned int Bit = (1 << PLAYER::PLAYER_ID());
				auto var0 = globalHandle(1625435 + 1 + PLAYER::PLAYER_ID() * 560 + 491).As<std::uint64_t>();
				auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
				uint64_t args[8] = { 1000837481, PLAYER::PLAYER_PED_ID(), 10000, 0, 0, var0, var1, var1 };
				Hooking::trigger_script_event(1, args, 8, Bit);
			}
			else if (i == 1) {
				for (int i = 0; i < 33; i++) {
					unsigned int Bit = (1 << i);
					auto var0 = globalHandle(1625435 + 1 + i * 560 + 491).As<std::uint64_t>();
					auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
					uint64_t args[8] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 10000, 0, 0, var0, var1, var1 };
					Hooking::trigger_script_event(1, args, 8, Bit);
				}
			}
			else {
				unsigned int Bit = (1 << Features::Online::selectedPlayer);
				auto var0 = globalHandle(1625435 + 1 + Features::Online::selectedPlayer * 560 + 491).As<std::uint64_t>();
				auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
				uint64_t args[8] = { 1000837481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 10000, 0, 0, var0, var1, var1 };
				Hooking::trigger_script_event(1, args, 8, Bit);
			}
		});
	}
}




void HypnoScript::HypnoScriptMain() {
	script = fp + HypnoScript::file + last;
	moneydrop();
	stealth();
	//tse();
	weather();
	kick();
	tp();
	transaction();
	for (int i = 0; i < getLines(script); i++) {
		if (checkCommand(prefix[0] + h_key, i)) {
			keypressed(0x6B, "+");
		}
	}
	for (int i = 0; i < getLines(script); i++) {
		if (checkCommand(prefix[0] + h_shooting + sel_pl[0] + ")", i)) {
			shooting1(sel_pl[0]);
		}
	}
	for (int i = 0; i < getLines(script); i++) {
		if (checkCommand(prefix[0] + h_shooting + sel_pl[1] + ")", i)) {
			shooting1(sel_pl[1]);
		}
	}
	for (int i = 0; i < getLines(script); i++) {
		if (checkCommand(prefix[0] + h_shooting + sel_pl[2] + ")", i)) {
			shooting1(sel_pl[2]);
		}
	}
}