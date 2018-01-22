#include "Unell_Script.h"

#define nevermind "[Закрыть]"
#define back "[Назад]"
//SUB WELCOME MENU//
#define SUB_MENU_TALENT_OPTION_1 "Изучить таланты"
#define SUB_MENU_TALENT_OPTION_2 "Сбросить таланты"
/////////////////////NPC ID MENU////////////////////////////////

#define EMOTE_NO_VIP "Извините, этот нпц доступен только для VIP игроков..."

enum Enchants
{
	ENCHANT_WEP_BERSERKING = 3789,
	ENCHANT_WEP_BLADE_WARD = 3869,
	ENCHANT_WEP_BLOOD_DRAINING = 3870,
	ENCHANT_WEP_ACCURACY = 3788,
	ENCHANT_WEP_AGILITY_1H = 1103,
	ENCHANT_WEP_SPIRIT = 3844,
	ENCHANT_WEP_BATTLEMASTER = 2675,
	ENCHANT_WEP_BLACK_MAGIC = 3790,
	ENCHANT_WEP_ICEBREAKER = 3239,
	ENCHANT_WEP_LIFEWARD = 3241,
	ENCHANT_WEP_MIGHTY_SPELL_POWER = 3834, // One-hand
	ENCHANT_WEP_EXECUTIONER = 3225,
	ENCHANT_WEP_POTENCY = 3833,
	ENCHANT_WEP_TITANGUARD = 3851,
	ENCHANT_2WEP_MASSACRE = 3827,
	ENCHANT_2WEP_SCOURGEBANE = 3247,
	ENCHANT_2WEP_GIANT_SLAYER = 3251,
	ENCHANT_2WEP_GREATER_SPELL_POWER = 3854,
	ENCHANT_2WEP_AGILITY = 2670,
	ENCHANT_2WEP_MONGOOSE = 2673,

	ENCHANT_SHIELD_DEFENSE = 1952,
	ENCHANT_SHIELD_INTELLECT = 1128,
	ENCHANT_SHIELD_RESILIENCE = 3229,
	ENCHANT_SHIELD_BLOCK = 2655,
	ENCHANT_SHIELD_STAMINA = 1071,
	ENCHANT_SHIELD_TOUGHSHIELD = 2653,
	ENCHANT_SHIELD_TITANIUM_PLATING = 3849,

	ENCHANT_HEAD_BLISSFUL_MENDING = 3819,
	ENCHANT_HEAD_BURNING_MYSTERIES = 3820,
	ENCHANT_HEAD_DOMINANCE = 3796,
	ENCHANT_HEAD_SAVAGE_GLADIATOR = 3842,
	ENCHANT_HEAD_STALWART_PROTECTOR = 3818,
	ENCHANT_HEAD_TORMENT = 3817,
	ENCHANT_HEAD_TRIUMPH = 3795,
	ENCHANT_HEAD_ECLIPSED_MOON = 3815,
	ENCHANT_HEAD_FLAME_SOUL = 3816,
	ENCHANT_HEAD_FLEEING_SHADOW = 3814,
	ENCHANT_HEAD_FROSTY_SOUL = 3812,
	ENCHANT_HEAD_TOXIC_WARDING = 3813,

	ENCHANT_SHOULDER_MASTERS_AXE = 3835,
	ENCHANT_SHOULDER_MASTERS_CRAG = 3836,
	ENCHANT_SHOULDER_MASTERS_PINNACLE = 3837,
	ENCHANT_SHOULDER_MASTERS_STORM = 3838,
	ENCHANT_SHOULDER_GREATER_AXE = 3808,
	ENCHANT_SHOULDER_GREATER_CRAG = 3809,
	ENCHANT_SHOULDER_GREATER_GLADIATOR = 3852,
	ENCHANT_SHOULDER_GREATER_PINNACLE = 3811,
	ENCHANT_SHOULDER_GREATER_STORM = 3810,
	ENCHANT_SHOULDER_DOMINANCE = 3794,
	ENCHANT_SHOULDER_TRIUMPH = 3793,

	ENCHANT_CLOAK_DARKGLOW_EMBROIDERY = 3728,
	ENCHANT_CLOAK_SWORDGUARD_EMBROIDERY = 3730,
	ENCHANT_CLOAK_LIGHTWEAVE_EMBROIDERY = 3722,
	ENCHANT_CLOAK_SPRINGY_ARACHNOWEAVE = 3859,
	ENCHANT_CLOAK_WISDOM = 3296,
	ENCHANT_CLOAK_TITANWEAVE = 1951,
	ENCHANT_CLOAK_SPELL_PIERCING = 3243,
	ENCHANT_CLOAK_SHADOW_ARMOR = 3256,
	ENCHANT_CLOAK_MIGHTY_ARMOR = 3294,
	ENCHANT_CLOAK_MAJOR_AGILITY = 1099,
	ENCHANT_CLOAK_GREATER_SPEED = 3831,

	ENCHANT_LEG_EARTHEN = 3853,
	ENCHANT_LEG_FROSTHIDE = 3822,
	ENCHANT_LEG_ICESCALE = 3823,
	ENCHANT_LEG_BRILLIANT_SPELLTHREAD = 3719,
	ENCHANT_LEG_SAPPHIRE_SPELLTHREAD = 3721,
	ENCHANT_LEG_DRAGONSCALE = 3331,
	ENCHANT_LEG_WYRMSCALE = 3332,

	ENCHANT_GLOVES_GREATER_BLASTING = 3249,
	ENCHANT_GLOVES_ARMSMAN = 3253,
	ENCHANT_GLOVES_CRUSHER = 1603,
	ENCHANT_GLOVES_AGILITY = 3222,
	ENCHANT_GLOVES_PRECISION = 3234,
	ENCHANT_GLOVES_EXPERTISE = 3231,

	ENCHANT_BRACERS_MAJOR_STAMINA = 3850,
	ENCHANT_BRACERS_SUPERIOR_SP = 2332,
	ENCHANT_BRACERS_GREATER_ASSUALT = 3845,
	ENCHANT_BRACERS_MAJOR_SPIRT = 1147,
	ENCHANT_BRACERS_EXPERTISE = 3231,
	ENCHANT_BRACERS_GREATER_STATS = 2661,
	ENCHANT_BRACERS_INTELLECT = 1119,
	ENCHANT_BRACERS_FURL_ARCANE = 3763,
	ENCHANT_BRACERS_FURL_FIRE = 3759,
	ENCHANT_BRACERS_FURL_FROST = 3760,
	ENCHANT_BRACERS_FURL_NATURE = 3762,
	ENCHANT_BRACERS_FURL_SHADOW = 3761,
	ENCHANT_BRACERS_FURL_ATTACK = 3756,
	ENCHANT_BRACERS_FURL_STAMINA = 3757,
	ENCHANT_BRACERS_FURL_SPELLPOWER = 3758,

	ENCHANT_CHEST_POWERFUL_STATS = 3832,
	ENCHANT_CHEST_SUPER_HEALTH = 3297,
	ENCHANT_CHEST_GREATER_MAINA_REST = 2381,
	ENCHANT_CHEST_EXCEPTIONAL_RESIL = 3245,
	ENCHANT_CHEST_GREATER_DEFENSE = 1953,

	ENCHANT_BOOTS_GREATER_ASSULT = 1597,
	ENCHANT_BOOTS_TUSKARS_VITLIATY = 3232,
	ENCHANT_BOOTS_SUPERIOR_AGILITY = 983,
	ENCHANT_BOOTS_GREATER_SPIRIT = 1147,
	ENCHANT_BOOTS_GREATER_VITALITY = 3244,
	ENCHANT_BOOTS_ICEWALKER = 3826,
	ENCHANT_BOOTS_GREATER_FORTITUDE = 1075,
	ENCHANT_BOOTS_NITRO_BOOTS = 3606,
	ENCHANT_BOOTS_PYRO_ROCKET = 3603,
	ENCHANT_BOOTS_HYPERSPEED = 3604,
	ENCHANT_BOOTS_ARMOR_WEBBING = 3860,

	ENCHANT_RING_ASSULT = 3839,
	ENCHANT_RING_GREATER_SP = 3840,
	ENCHANT_RING_STAMINA = 3791,

	ENCHANT_BRACERS_SOKET = 3717,
	ENCHANT_GLOVERS_SOKET = 3723,

};

enum CLASSES_MENU_ID
{
	MENU_WARRIOR = 1,
	MENU_PALADIN = 2,
	MENU_HUNTER = 3,
	MENU_ROGUE = 4,
	MENU_PRIEST = 5,
	MENU_DEATH_K = 6,
	MENU_SHAMAN = 7,
	MENU_MAGE = 8,
	MENU_WARLOCK = 9,
	MENU_DRUID = 10
};

enum OPTION_MENU_ID //11->50
{
	OPTION_MENU_ID_1 = 11,
	OPTION_MENU_ID_2 = 12,
	OPTION_MENU_ID_3 = 13,
	OPTION_MENU_ID_4 = 14
};

enum SUB_OPTION_MENU_ID //51->100
{
	SUB_OPTION_MENU_ID_1 = 51,
	SUB_OPTION_MENU_ID_2 = 52,
	SUB_OPTION_MENU_ID_3 = 53,
	SUB_OPTION_MENU_ID_4 = 54
};

enum BACK_OPTION //1000->
{
	BACK_OPTION_MENU_1 = 1000, //Main Menu
};

enum eIcons
{
	CHAT_ICON = 0,
	VENDOR_ICON = 1,
	FLIGHT_ICON = 2,
	TRAINER_ICON = 3,
	GEAR_ICON = 4,
	GEAR_ICON_2 = 5,
	BANK_ICON = 6,
	CHAT_DOTS_ICON = 7,
	TABARD_ICON = 8,
	SWORDS_ICON = 9,
	GOLD_DOT_ICON = 10
};

enum war_spell
{
	war_spell_Overpower = 7384,
	war_spell_Battle_Shout = 47436,
	war_spell_Heroic_Strike = 47450,
	war_spell_Charge = 11578,
	war_spell_Rend = 47465,
	war_spell_Thunder_Clap = 47502,
	war_spell_Victory_Rush = 34428,
	war_spell_Hamstring = 1715,
	war_spell_Bloodrage = 2687,
	war_spell_Defensive_Stance = 71,
	war_spell_Sunder_Armor = 7386,
	war_spell_Taunt = 355,
	war_spell_Shield_Bash = 72,
	war_spell_Demoralizing_Shout = 47437,
	war_spell_Revenge = 57823,
	war_spell_Mocking_Blow = 694,
	war_spell_Shield_Block = 2565,
	war_spell_Disarm = 676,
	war_spell_Cleave = 47520,
	war_spell_Retaliation = 20230,
	war_spell_Stance_Mastery = 12678,
	war_spell_Execute = 47471,
	war_spell_Challenging_Shout = 1161,
	war_spell_Shield_Wall = 871,
	war_spell_Berserker_Stance = 2458,
	war_spell_Intercept = 20252,
	war_spell_Slam = 47475,
	war_spell_Berserker_Rage = 18499,
	war_spell_Whirlwind = 1680,
	war_spell_Pummel = 6552,
	war_spell_Sheild_Slam = 47488,
	war_spell_Recklessness = 1719,
	war_spell_Spell_Reflection = 23920,
	war_spell_Commanding_Shout = 47440,
	war_spell_Intervene = 3411,
	war_spell_Shattering_Throw = 64382,
	war_spell_Enraged_Regeneration = 55694,
	war_spell_Heroic_Throw = 57755,
	war_spell_Dual_Wield = 42459,
	war_spell_Intimidating_Shout = 5246,
	war_spell_Parry = 3127,

	//Talent - War
	war_spell_Devastate = 47498,	// Talent - Proto
	war_spell_Mortal_Strike = 47486 // Talent - Arms

};

enum pala_spell
{
	pala_spell_Parry = 3127,
	pala_spell_Concentration_Aura = 19746,
	pala_spell_Divine_Intervention = 19752,
	pala_spell_Plate_Mail_skill = 750,
	pala_spell_Devotion_Aura = 48942,
	pala_spell_Holy_Light = 48782,
	pala_spell_Blessing_of_Might = 48932,
	pala_spell_Judgement_of_Light = 20271,
	pala_spell_Divine_Protection = 498,
	pala_spell_Hammer_of_Justice = 10308,
	pala_spell_Purify = 1152,
	pala_spell_Hand_of_Protection = 10278,
	pala_spell_Lay_on_Hands = 48788,
	pala_spell_Judgement_of_Wisdom = 53408,
	pala_spell_Redemption = 48950,
	pala_spell_Blessing_of_Wisdom = 48936,
	pala_spell_Righteous_Defense = 31789,
	pala_spell_Hand_of_Reckoning = 62124,
	pala_spell_Retribution_Aura = 54043,
	pala_spell_Righteous_Fury = 25780,
	pala_spell_Hand_of_Freedom = 1044,
	pala_spell_Blessing_of_Kings = 20217,
	pala_spell_Consecration = 48819,
	pala_spell_Exorcism = 48801,
	pala_spell_Flash_of_Light = 48785,
	pala_spell_Sense_Undead = 5502,
	pala_spell_Seal_of_Justice = 20164,
	pala_spell_Turn_Evil = 10326,
	pala_spell_Hand_of_Salvation = 1038,
	pala_spell_Judgement_of_Justice = 53407,
	pala_spell_Shadow_Resistance_Aura = 48943,
	pala_spell_Seal_of_Light = 20165,
	pala_spell_Frost_Resistance_Aura = 48945,
	pala_spell_Divine_Shield = 642,
	pala_spell_Fire_Resistance_Aura = 48947,
	pala_spell_Seal_of_Wisdom = 20166,
	pala_spell_Cleanse = 4987,
	pala_spell_Hammer_of_Wrath = 48806,
	pala_spell_Hand_of_Sacrifice = 6940,
	pala_spell_Holy_Wrath = 48817,
	pala_spell_Greater_Blessing_of_Might = 48934,
	pala_spell_Greater_Blessing_of_Wisdom = 48938,
	pala_spell_Greater_Blessing_of_Kings = 25898,
	pala_spell_Crusader_Aura = 32223,
	pala_spell_Avenging_Wrath = 31884,
	pala_spell_Divine_Plea = 54428,
	pala_spell_Shield_of_Righteousness = 61411,
	pala_spell_Sacred_Shield = 53601,
	pala_spell_Seal_of_Vengeance = 31801,   // Alliance
	pala_spell_Warhorse = 13819,			// Alliance
	pala_spell_Charger = 23214,				// Alliance
	pala_spell_Seal_of_Corruption = 53736,  // Horde
	pala_spell_Thalassian_Warhorse = 34769, // Horde
	pala_spell_Thalassian_Charger = 34767,  // Horde

	//Talent - Paladin
	pala_spell_Holy_Shield = 48952,					  // Talent - Protection
	pala_spell_Avengers_Shield = 48827,				  // Talent - Protection
	pala_spell_Greater_Blessing_of_Sanctuary = 25899, // Talents - Protection
	pala_spell_Holy_Shock = 48825,					  // Talents - Holy
};

enum mage_spell
{
	mage_spell_Arcane_Explosion = 42921,
	mage_spell_Frostbolt = 42842,
	mage_spell_Arcane_Intellect = 42995,
	mage_spell_Fireball = 42833,
	mage_spell_Conjure_Water = 27090,
	mage_spell_Conjure_Food = 33717,
	mage_spell_Fire_Blast = 42873,
	mage_spell_Arcane_Missiles = 42846,
	mage_spell_Polymorph = 12826,
	mage_spell_Polymorph_Turtle = 28271,
	mage_spell_Polymorph_Turkey = 61780,
	mage_spell_Polymorph_Rabbit = 61721,
	mage_spell_Polymorph_Pig = 28272,
	mage_spell_Frost_Nova = 42917,
	mage_spell_Dampen_Magic = 43015,
	mage_spell_Slow_Fall = 130,
	mage_spell_Flamestrike = 42926,
	mage_spell_Amplify_Magic = 43017,
	mage_spell_Remove_Curse = 475,
	mage_spell_Blink = 1953,
	mage_spell_Blizzard = 42940,
	mage_spell_Evocation = 12051,
	mage_spell_Fire_Ward = 43010,
	mage_spell_Mana_Shield = 43020,
	mage_spell_Frost_Ward = 43012,
	mage_spell_Scorch = 42859,
	mage_spell_Counterspell = 2139,
	mage_spell_Cone_of_Cold = 42931,
	mage_spell_Conjure_Mana_Gem = 42985,
	mage_spell_Ice_Armor = 43008,
	mage_spell_Ice_Block = 45438,
	mage_spell_Mage_Armor = 43024,
	mage_spell_Arcane_Brilliance = 43002,
	mage_spell_Molten_Armor = 43046,
	mage_spell_Arcane_Blast = 42897,
	mage_spell_Ice_Lance = 42914,
	mage_spell_Invisibility = 66,
	mage_spell_Ritual_of_Refreshment = 58659,
	mage_spell_Spellsteal = 30449,
	mage_spell_Conjure_Refreshment = 42956,
	mage_spell_Frostfire_Bolt = 47610,
	mage_spell_Dalaran_Brilliance = 61316,
	mage_spell_Dalaran_Intellect = 61024,
	mage_spell_Mirror_Image = 55342,
	mage_spell_Portal_Dalaran = 53142,
	mage_spell_Frost_Armor = 7301,

	mage_spell_Teleport_Exodar = 32271,	// Alliance
	mage_spell_Teleport_Theramore = 49359, // Alliance
	mage_spell_Teleport_Darnassus = 3565,  // Alliance
	mage_spell_Teleport_Shattrath = 33690, // Alliance
	mage_spell_Teleport_Ironforge = 3562,  // Alliance
	mage_spell_Teleport_Stromwind = 3561,  // Alliance
	mage_spell_Portal_Darnassus = 11419,   // Alliance
	mage_spell_Portal_Exodar = 32266,	  // Alliance
	mage_spell_Portal_Ironforge = 11416,   // Alliance
	mage_spell_Portal_Shattrath = 33691,   // Alliance
	mage_spell_Portal_Theramore = 49360,   // Alliance

	mage_spell_Teleport_Orgrimmar = 3567,	 // Horde
	mage_spell_Teleport_Shattrath_H = 35715,  // Horde
	mage_spell_Teleport_Thunder_Bluff = 3566, // Horde
	mage_spell_Teleport_Stonard = 49358,	  // Horde
	mage_spell_Teleport_Silvermoon = 32272,   // Horde
	mage_spell_Teleport_Undercity = 3563,	 // Horde
	mage_spell_Portal_Orgrimmar = 11417,	  // Horde
	mage_spell_Portal_Shattrath_H = 35717,	// Horde
	mage_spell_Portal_Silvermoon = 32267,	 // Horde
	mage_spell_Portal_Stonard = 49361,		  // Horde
	mage_spell_Portal_Thunder_Bluff = 11420,  // Horde
	mage_spell_Portal_Undercity = 11418,	  // Horde

	//Talent - Mage
	mage_spell_Pyroblast = 42891,	  // Talent - Fire
	mage_spell_Ice_Barrier = 43039,	// Talent - Frost
	mage_spell_Living_Bomb = 55360,	// Talent - Fire
	mage_spell_Dragons_Breath = 42950, // Talent - Fire
	mage_spell_Blast_Wave = 42945,	 // Talent - Fire
	mage_spell_Arcane_Barrage = 44781  // Talent - Arcane

};

enum dk_spell
{
	dk_spell_Parry = 3127,
	dk_spell_Pestilence = 50842,
	dk_spell_Blood_Boil = 49941,
	dk_spell_Blood_Strike = 49930,
	dk_spell_Strangulate = 47476,
	dk_spell_Blood_Tap = 45529,
	dk_spell_Path_of_Frost = 3714,
	dk_spell_Dark_Command = 56222,
	dk_spell_Death_Pact = 48743,
	dk_spell_Frost_Presence = 48263,
	dk_spell_Icy_Touch = 49909,
	dk_spell_Mind_Freeze = 47528,
	dk_spell_Chains_of_Ice = 45524,
	dk_spell_Icebound_Fortitude = 48792,
	dk_spell_Horn_of_Winter = 57623,
	dk_spell_Rune_Strike = 56815,
	dk_spell_Empower_Rune_Weapon = 47568,
	dk_spell_Death_Coil = 49895,
	dk_spell_Death_Gate = 50977,
	dk_spell_Plague_Strike = 49921,
	dk_spell_Death_Grip = 49576,
	dk_spell_Raise_Dead = 46584,
	dk_spell_Death_and_Decay = 49938,
	dk_spell_Anti_Magic_Shell = 48707,
	dk_spell_Unholy_Presence = 48265,
	dk_spell_Raise_Ally = 61999,
	dk_spell_Army_of_the_Dead = 42650,
	dk_spell_Runeforging_skill = 53428,
	dk_spell_Uknowas = 53331,
	dk_spell_Uknowah = 54447,
	dk_spell_Uknowai = 53342,
	dk_spell_Uknowaz = 54446,
	dk_spell_Uknowan = 53323,
	dk_spell_Uknowab = 53344,
	dk_spell_Uknowav = 70164,
	dk_spell_Uknowaj = 62158,
	dk_spell_Uknowaq = 33391,
	dk_spell_Acherus_Deathcharger = 48778,
	dk_spell_Obliterate = 51425,
	dk_spell_Death_Strike = 49924,

	//Talent - Deathknight
	dk_spell_Heart_Strike = 55262,	// Talent - Blood
	dk_spell_Frost_Strike = 55268,	// Talent - Frost
	dk_spell_Howling_Blast = 51411,   // Talent - Frost
	dk_spell_Scourge_Strike = 55271,  // Talent - Unholy
	dk_spell_Corpse_Explosion = 51328 // Talent - Unholy

};

enum druid_spell
{
	druid_spell_Healing_Touch = 48378,
	druid_spell_Mark_of_the_Wild = 48469,
	druid_spell_Wrath = 48461,
	druid_spell_Moonfire = 48463,
	druid_spell_Rejuvenation = 48441,
	druid_spell_Thorns = 53307,
	druid_spell_Entangling_Roots = 53308,
	druid_spell_Bear_Form = 5487,
	druid_spell_Demoralizing_Roar = 48560,
	druid_spell_Growl = 6795,
	druid_spell_Maul = 48480,
	druid_spell_Natures_Grasp = 53312,
	druid_spell_Teleport_Moonglade = 18960,
	druid_spell_Enrage = 5229,
	druid_spell_Regrowth = 48443,
	druid_spell_Revive = 50763,
	druid_spell_Bash = 8983,
	druid_spell_Cure_Poison = 8946,
	druid_spell_Aquatic_Form = 1066,
	druid_spell_Swipe_Bear = 48562,
	druid_spell_Travel_Form = 783,
	druid_spell_Faerie_Fire = 770,
	druid_spell_Faerie_Fire_Feral = 16857,
	druid_spell_Hibernate = 18658,
	druid_spell_Cat_Form = 768,
	druid_spell_Feral_Charge_Bear = 16979,
	druid_spell_Feral_Charge_Cat = 49376,
	druid_spell_Prowl = 5215,
	druid_spell_Rebirth = 48477,
	druid_spell_Rip = 49800,
	druid_spell_Starfire = 48465,
	druid_spell_Shred = 48572,
	druid_spell_Soothe_Animal = 26995,
	druid_spell_Rake = 48574,
	druid_spell_Remove_Curse = 2782,
	druid_spell_Tigers_Fury = 50213,
	druid_spell_Abolish_Poison = 2893,
	druid_spell_Dash = 33357,
	druid_spell_Challenging_Roar = 5209,
	druid_spell_Cower = 48575,
	druid_spell_Tranquility = 48447,
	druid_spell_Ferocious_Bite = 48577,
	druid_spell_Ravage = 48579,
	druid_spell_Track_Humanoids = 5225,
	druid_spell_Frenzied_Regeneration = 22842,
	druid_spell_Pounce = 49803,
	druid_spell_Dire_Bear_Form = 9634,
	druid_spell_Feline_Grace = 20719,
	druid_spell_Hurricane = 48467,
	druid_spell_Innervate = 29166,
	druid_spell_Savage_Defense = 62600,
	druid_spell_Barkskin = 22812,
	druid_spell_Gift_of_the_Wild = 48470,
	druid_spell_Mangle_Bear = 48564,
	druid_spell_Mangle_Cat = 48566,
	druid_spell_Flight_Form = 33943,
	druid_spell_Maim = 49802,
	druid_spell_Lifebloom = 48451,
	druid_spell_Lacerate = 48568,
	druid_spell_Cyclone = 33786,
	druid_spell_Swift_Flight_Form = 40120,
	druid_spell_Swipe_Cat = 62078,
	druid_spell_Savage_Roar = 52610,
	druid_spell_Nourish = 50464,
	druid_spell_Claw_1 = 1082,
	druid_spell_Claw = 48570,

	//Talent - Druid
	druid_spell_Typhoon = 61384,	 // Talent - Balance
	druid_spell_Starfall = 53201,	// Talent - Balance
	druid_spell_Wild_Growth = 53251, // Talent - Restoration
	druid_spell_Insect_Swarm = 48468 // Talent - Balance

};

enum shaman_spell
{
	shaman_spell_Earth_Elemental_Totem = 2062,
	shaman_spell_Healing_Wave = 49273,
	shaman_spell_Lightning_Bolt = 49238,
	shaman_spell_Rockbiter_Weapon = 10399,
	shaman_spell_Earth_Shock = 49231,
	shaman_spell_Stoneskin_Totem = 58753,
	shaman_spell_Earthbind_Totem = 2484,
	shaman_spell_Lightning_Shield = 49281,
	shaman_spell_Stoneclaw_Totem = 58582,
	shaman_spell_Flame_Shock = 49233,
	shaman_spell_Flametongue_Weapon = 58790,
	shaman_spell_Searing_Totem = 58704,
	shaman_spell_Strength_of_Earth_Totem = 58643,
	shaman_spell_Ancestral_Spirit = 49277,
	shaman_spell_Fire_Nova = 61657,
	shaman_spell_Purge = 8012,
	shaman_spell_Cure_Toxins = 526,
	shaman_spell_Ghost_Wolf = 2645,
	shaman_spell_Wind_Shear = 57994,
	shaman_spell_Tremor_Totem = 8143,
	shaman_spell_Frost_Shock = 49236,
	shaman_spell_Frostbrand_Weapon = 58796,
	shaman_spell_Healing_Stream_Totem = 58757,
	shaman_spell_Lesser_Healing_Wave = 49276,
	shaman_spell_Water_Shield = 57960,
	shaman_spell_Water_Breathing = 131,
	shaman_spell_Frost_Resistance_Totem = 58745,
	shaman_spell_Far_Sight = 6196,
	shaman_spell_Magma_Totem = 58734,
	shaman_spell_Mana_Spring_Totem = 58774,
	shaman_spell_Fire_Resistance_Totem = 58739,
	shaman_spell_Flametongue_Totem = 58656,
	shaman_spell_Water_Walking = 546,
	shaman_spell_Astral_Recall = 556,
	shaman_spell_Call_of_the_Elements = 66842,
	shaman_spell_Earthliving_Weapon = 51994,
	shaman_spell_Grounding_Totem = 8177,
	shaman_spell_Nature_Resistance_Totem = 58749,
	shaman_spell_Reincarnation = 20608,
	shaman_spell_Totemic_Recall = 36936,
	shaman_spell_Windfury_Weapon = 58804,
	shaman_spell_Chain_Lightning = 49271,
	shaman_spell_Windfury_Totem = 8512,
	shaman_spell_Sentry_Totem = 6495,
	shaman_spell_Cleansing_Totem = 8170,
	shaman_spell_Call_of_the_Ancestors = 66843,
	shaman_spell_Chain_Heal = 55459,
	shaman_spell_Call_of_the_Spirits = 66844,
	shaman_spell_Wrath_of_Air_Totem = 3738,
	shaman_spell_Fire_Elemental_Totem = 2894,
	shaman_spell_Lava_Burst = 60043,
	shaman_spell_Hex = 51514,
	shaman_spell_Bloodlust = 2825, // Horde
	shaman_spell_Heroism = 32182,  // Alliance

	//Talent - Shaman
	shaman_spell_Riptide = 61301,		 // Talent - Restoration
	shaman_spell_Earth_Shield = 49284,   // Talent - Restoration
	shaman_spell_Totem_of_Wrath = 57722, // Talent - Elemental
	shaman_spell_Thunderstorm = 59159	// Talent - Elemental

};

enum hunter_spell
{
	hunter_spell_Scorpid_Sting = 3043,
	hunter_spell_Parry = 3127,
	hunter_spell_Rapid_Fire = 3045,
	hunter_spell_Viper_Sting = 3034,
	hunter_spell_Track_Beasts = 1494,
	hunter_spell_Aspect_of_the_Monkey = 13163,
	hunter_spell_Raptor_Strike = 48996,
	hunter_spell_Serpent_Sting = 49001,
	hunter_spell_Arcane_Shot = 49045,
	hunter_spell_Hunters_Mark = 53338,
	hunter_spell_Concussive_Shot = 5116,
	hunter_spell_Aspect_of_the_Hawk = 27044,
	hunter_spell_Call_Pet = 883,
	hunter_spell_Dismiss_Pet = 2641,
	hunter_spell_Feed_Pet = 6991,
	hunter_spell_Revive_Pet = 982,
	hunter_spell_Tame_Beast = 1515,
	hunter_spell_Track_Humanoids = 19883,
	hunter_spell_Distracting_Shot = 20736,
	hunter_spell_Mend_Pet = 48990,
	hunter_spell_Wing_Clip = 2974,
	hunter_spell_Eagle_Eye = 6197,
	hunter_spell_Eyes_of_the_Beast = 1002,
	hunter_spell_Scare_Beast = 14327,
	hunter_spell_Aspect_of_the_Cheetah = 5118,
	hunter_spell_Immolation_Trap = 49056,
	hunter_spell_Mongoose_Bite = 53339,
	hunter_spell_Multi_Shot = 49048,
	hunter_spell_Track_Undead = 19884,
	hunter_spell_Aspect_of_the_Viper = 34074,
	hunter_spell_Disengage = 781,
	hunter_spell_Freezing_Trap = 14311,
	hunter_spell_Beast_Lore = 1462,
	hunter_spell_Track_Hidden = 19885,
	hunter_spell_Track_Elementals = 19880,
	hunter_spell_Frost_Trap = 13809,
	hunter_spell_Aspect_of_the_Beast = 13161,
	hunter_spell_Feign_Death = 5384,
	hunter_spell_Flare = 1543,
	hunter_spell_Track_Demons = 19878,
	hunter_spell_Explosive_Trap = 49067,
	hunter_spell_Aspect_of_the_Pack = 13159,
	hunter_spell_Track_Giants = 19882,
	hunter_spell_Volley = 58434,
	hunter_spell_Aspect_of_the_Wild = 49071,
	hunter_spell_Steady_Shot = 49052,
	hunter_spell_Track_Dragonkin = 19879,
	hunter_spell_Deterrence = 19263,
	hunter_spell_Tranquilizing_Shot = 19801,
	hunter_spell_Kill_Command = 34026,
	hunter_spell_Snake_Trap = 34600,
	hunter_spell_Misdirection = 34477,
	hunter_spell_Kill_Shot = 61006,
	hunter_spell_Aspect_of_the_Dragonhawk = 61847,
	hunter_spell_Masters_Call = 53271,
	hunter_spell_Freezing_Arrow = 60192,
	hunter_spell_Call_Stabled_Pet = 62757,
	hunter_spell_Dual_Wield = 42459,

	//Talent - Hunter
	hunter_spell_Wyvern_Sting = 49012,   // Talent - Survival
	hunter_spell_Explosive_Shot = 60053, // Talent - Survival
	hunter_spell_Conterattack = 48999,   // Talent - Survival
	hunter_spell_Aimed_Shot = 49050		 // Talent - Marksmanship

};

enum rogue_spell
{
	rogue_spell_Parry = 3127,
	rogue_spell_Dual_Wield = 42459,
	rogue_spell_Eviscerate = 48668,
	rogue_spell_Sinister_Strike = 48638,
	rogue_spell_Stealth = 1784,
	rogue_spell_Backstab = 48657,
	rogue_spell_Pick_Pocket = 921,
	rogue_spell_Gouge = 1776,
	rogue_spell_Evasion = 26669,
	rogue_spell_Sap = 51724,
	rogue_spell_Slice_and_Dice = 6774,
	rogue_spell_Sprint = 11305,
	rogue_spell_Kick = 1766,
	rogue_spell_Garrote = 48676,
	rogue_spell_Feint = 48659,
	rogue_spell_Lockpicking_skill = 1804,
	rogue_spell_Expose_Armor = 8647,
	rogue_spell_Ambush = 48691,
	rogue_spell_Dismantle = 51722,
	rogue_spell_Rupture = 48672,
	rogue_spell_Distract = 1725,
	rogue_spell_Vanish = 26889,
	rogue_spell_Detect_Traps = 2836,
	rogue_spell_Cheap_Shot = 1833,
	rogue_spell_Disarm_Trap = 1842,
	rogue_spell_Kidney_Shot = 8643,
	rogue_spell_Blind = 2094,
	rogue_spell_Safe_Fall = 1860,
	rogue_spell_Envenom = 57993,
	rogue_spell_Deadly_Throw = 48674,
	rogue_spell_Cloak_of_Shadows = 31224,
	rogue_spell_Shiv = 5938,
	rogue_spell_Tricks_of_the_Trade = 57934,
	rogue_spell_Fan_of_Knives = 51723,

	//Talent - Rogue
	rogue_spell_Hemorrhage = 48660, // Talent - Subtlety
	rogue_spell_Mutilate = 48666	// Talent - Assassination

};

enum priest_spell
{
	priest_spell_Cure_Disease = 528,
	priest_spell_Lesser_Heal = 2053,
	priest_spell_Power_Word_Fortitude = 48161,
	priest_spell_Smite = 48123,
	priest_spell_Shadow_Word_Pain = 48125,
	priest_spell_Power_Word_Shield = 48066,
	priest_spell_Fade = 586,
	priest_spell_Renew = 48068,
	priest_spell_Mind_Blast = 48127,
	priest_spell_Resurrection = 48171,
	priest_spell_Inner_Fire = 48168,
	priest_spell_Psychic_Scream = 10890,
	priest_spell_Heal = 6064,
	priest_spell_Dispel_Magic = 988,
	priest_spell_Devouring_Plague = 48300,
	priest_spell_Fear_Ward = 6346,
	priest_spell_Flash_Heal = 48071,
	priest_spell_Holy_Fire = 48135,
	priest_spell_Holy_Nova = 48078,
	priest_spell_Mind_Soothe = 453,
	priest_spell_Shackle_Undead = 10955,
	priest_spell_Mind_Vision = 10909,
	priest_spell_Mana_Burn = 8129,
	priest_spell_Divine_Spirit = 48073,
	priest_spell_Mind_Control = 605,
	priest_spell_Prayer_of_Healing = 48072,
	priest_spell_Shadow_Protection = 48169,
	priest_spell_Abolish_Disease = 552,
	priest_spell_Levitate = 1706,
	priest_spell_Greater_Heal = 48063,
	priest_spell_Prayer_of_Fortitude = 48162,
	priest_spell_Prayer_of_Shadow_Protection = 48170,
	priest_spell_Prayer_of_Spirit = 48074,
	priest_spell_Shadow_Word_Death = 48158,
	priest_spell_Binding_Heal = 48120,
	priest_spell_Shadowfiend = 34433,
	priest_spell_Prayer_of_Mending = 48113,
	priest_spell_Mass_Dispel = 32375,
	priest_spell_Divine_Hymn = 64843,
	priest_spell_Hymn_of_Hope = 64901,
	priest_spell_Mind_Sear = 53023,

	//Talent - Priest
	priest_spell_Vampiric_Touch = 48160,	// Talent - Shadow
	priest_spell_Penance = 53007,			// Talent - Discipline
	priest_spell_Lightwell = 48087,			// Talent - Holy
	priest_spell_Desperate_Prayer = 48173,  // Talent - Holy
	priest_spell_Circle_of_Healing = 48089, // Talent - Holy
	priest_spell_Mind_Flay = 48156			// Talent - Shadow

};

enum warlock_spell
{
	warlock_spell_Demon_Skin = 696,
	warlock_spell_Immolate = 47811,
	warlock_spell_Shadow_Bolt = 47809,
	warlock_spell_Summon_Imp = 688,
	warlock_spell_Corruption = 47813,
	warlock_spell_Curse_of_Weakness = 50511,
	warlock_spell_Life_Tap = 57946,
	warlock_spell_Curse_of_Agony = 47864,
	warlock_spell_Fear = 6215,
	warlock_spell_Create_Healthstone = 47878,
	warlock_spell_Drain_Soul = 47855,
	warlock_spell_Summon_Voidwalker = 697,
	warlock_spell_Health_Funnel = 47856,
	warlock_spell_Drain_Life = 47857,
	warlock_spell_Unending_Breath = 5697,
	warlock_spell_Create_Soulstone = 47884,
	warlock_spell_Searing_Pain = 47815,
	warlock_spell_Demon_Armor = 47889,
	warlock_spell_Rain_of_Fire = 47820,
	warlock_spell_Ritual_of_Summoning = 698,
	warlock_spell_Summon_Succubus = 712,
	warlock_spell_Eye_of_Kilrogg = 126,
	warlock_spell_Drain_Mana = 5138,
	warlock_spell_Sense_Demons = 5500,
	warlock_spell_Curse_of_Tongues = 11719,
	warlock_spell_Detect_Invisibility = 132,
	warlock_spell_Create_Firestone = 60220,
	warlock_spell_Banish = 18647,
	warlock_spell_Enslave_Demon = 61191,
	warlock_spell_Hellfire = 47823,
	warlock_spell_Summon_Felhunter = 691,
	warlock_spell_Curse_of_the_Elements = 47865,
	warlock_spell_Shadow_Ward = 47891,
	warlock_spell_Create_Spellstone = 47888,
	warlock_spell_Howl_of_Terror = 17928,
	warlock_spell_Death_Coil = 47860,
	warlock_spell_Soul_Fire = 47825,
	warlock_spell_Inferno = 1122,
	warlock_spell_Curse_of_Doom = 47867,
	warlock_spell_Ritual_of_Doom = 18540,
	warlock_spell_Fel_Armor = 47893,
	warlock_spell_Incinerate = 47838,
	warlock_spell_Soulshatter = 29858,
	warlock_spell_Ritual_of_Souls = 58887,
	warlock_spell_Seed_of_Corruption = 47836,
	warlock_spell_Shadowflame = 61290,
	warlock_spell_Demonic_Circle_Summon = 48018,
	warlock_spell_Demonic_Circle_Teleport = 48020,
	warlock_spell_Dreadsteed = 23161,

	//Talent - Warlock
	warlock_spell_Shadowburn = 47827,		   // Talent - Destruction
	warlock_spell_Shadowfury = 47847,		   // Talent - Destruction
	warlock_spell_Unstable_Affliction = 47843, // Talent - Affliction
	warlock_spell_Chaos_Bolt = 59172,		   // Talent - Destruction
	warlock_spell_Haunt = 59164,			   // Talent - Affliction
	warlock_spell_Dark_Pact = 59092			   // Talent - Affliction

};

void Enchant(Player *player, Item *item, uint32 enchantid)
{
	if (!item)
	{
		player->GetSession()->SendNotification("Вы должны одеть предмет, чтобы зачарить его!");
		return;
	}
	item->ClearEnchantment(PERM_ENCHANTMENT_SLOT);
	item->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantid, 0, 0);

	ChatHandler handler(player->GetSession());
	const ItemTemplate *temp = item->GetTemplate();
	ItemLocale const *itemLocale = sObjectMgr->GetItemLocale(temp->ItemId);
	char const *name = nullptr;
	if (itemLocale)
		name = itemLocale->Name[handler.GetSessionDbcLocale()].c_str();
	if ((!name || !*name) && temp)
		name = temp->Name1.c_str();
	if (!name)
		name = "Unknown item";

	player->GetSession()->SendNotification("|cff800080%s |cffFF0000Успешно зачаровано!", name);
}

void RemoveEnchant(Player *player, Item *item)
{
	if (!item)
	{
		player->GetSession()->SendNotification("У вас нет предметов, чтобы одеть их?");
		return;
	}

	ChatHandler handler(player->GetSession());
	const ItemTemplate *temp = item->GetTemplate();
	ItemLocale const *itemLocale = sObjectMgr->GetItemLocale(temp->ItemId);
	char const *name = nullptr;
	if (itemLocale)
		name = itemLocale->Name[handler.GetSessionDbcLocale()].c_str();
	if ((!name || !*name) && temp)
		name = temp->Name1.c_str();
	if (!name)
		name = "Unknown item";

	item->ClearEnchantment(PERM_ENCHANTMENT_SLOT);

	player->GetSession()->SendNotification("|cff800080%s |cffFF0000успешно разочарован!", name);
}

class ralph : public CreatureScript
{
  public:
	ralph() : CreatureScript("ralph") {}

	void static CreatePet(Player *player, Creature *creature, uint32 entry)
	{
		if (player->getClass() != CLASS_HUNTER)
		{
			creature->MonsterWhisper("Вы не Охотник!", player, false);
			player->CLOSE_GOSSIP_MENU();
			return;
		}

		if (player->GetPet())
		{
			creature->MonsterWhisper("У вас уже есть питомец!", player, false);
			player->CLOSE_GOSSIP_MENU();
			return;
		}

		Creature *creatureTarget = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
		if (!creatureTarget)
			return;

		Pet *pet = player->CreateTamedPetFrom(creatureTarget, 0);
		if (!pet)
			return;

		// kill original creature
		creatureTarget->setDeathState(JUST_DIED);
		creatureTarget->RemoveCorpse();
		creatureTarget->SetHealth(0);

		pet->SetPower(POWER_HAPPINESS, 10480000);

		// prepare visual effect for levelup
		pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
		pet->GetMap()->AddToMap(pet->ToCreature());

		// visual effect for levelup
		pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());

		pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);

		pet->UpdateAllStats();
		player->SetMinion(pet, true);

		pet->SavePetToDB(PET_SAVE_AS_CURRENT, 0);
		pet->InitTalentForLevel();
		player->PetSpellInitialize();

		player->CLOSE_GOSSIP_MENU();
		creature->MonsterWhisper("Поздравляю, вы получили нового питомца!", player, false);
	}

	bool OnGossipHello(Player *player, Creature *creature)
	{
		if (player->getClass() != CLASS_HUNTER)
		{
			creature->MonsterWhisper("Я могу обучать только охотников!", player, false);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}

		if (sConfigMgr->GetBoolDefault("Unell.NPC.Ralph.OnlyVIP", true) && !player->GetSession()->IsPremium())
		{
			creature->MonsterWhisper("Я могу помочь только VIP игрокам...", player, false);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}

		if (player->GetPet())
		{
			creature->MonsterWhisper("Вы должны отпустить или оставить своего текущего питомца, чтобы получить нового!", player, false);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}

		player->ADD_GOSSIP_ITEM(1, "|TInterface/ICONS/ability_hunter_beasttaming:30|t Получить питомца", GOSSIP_SENDER_MAIN, 30);

		if (player->CanTameExoticPets())
			player->ADD_GOSSIP_ITEM(1, "|TInterface/ICONS/ability_hunter_beastmastery:30|t Получить экзотического питомца", GOSSIP_SENDER_MAIN, 50);

		player->SEND_GOSSIP_MENU(1, creature->GetGUID());

		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{
		case 100:
			OnGossipHello(player, creature);
			break;

		case 150:
			player->CLOSE_GOSSIP_MENU();
			break;

		case 30:
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_bat:30|t Летучая мышь", GOSSIP_SENDER_MAIN, 18);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_bear:30|t Медведь", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_boar:30|t Вепрь", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_cat:30|t Кошка", GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_vulture:30|t Падальщик", GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_crab:30|t Краб", GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_crocolisk:30|t Кроколиск", GOSSIP_SENDER_MAIN, 7);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_dragonhawk:30|t Дракондор", GOSSIP_SENDER_MAIN, 17);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_gorilla:30|t Горилла", GOSSIP_SENDER_MAIN, 8);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_wolf:30|t Волк", GOSSIP_SENDER_MAIN, 9);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_hyena:30|t Гиена", GOSSIP_SENDER_MAIN, 10);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_moth:30|t Мотылёк", GOSSIP_SENDER_MAIN, 11);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_owl:30|t Сова", GOSSIP_SENDER_MAIN, 12);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_raptor:30|t Ящер", GOSSIP_SENDER_MAIN, 20);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_ravager:30|t Опустошитель", GOSSIP_SENDER_MAIN, 19);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_tallstrider:30|t Долгоног", GOSSIP_SENDER_MAIN, 13);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_scorpid:30|t Скорпион", GOSSIP_SENDER_MAIN, 414);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_spider:30|t Паук", GOSSIP_SENDER_MAIN, 16);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/spell_nature_guardianward:30|t Змей", GOSSIP_SENDER_MAIN, 21);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_turtle:30|t Черепаха", GOSSIP_SENDER_MAIN, 15);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_wasp:30|t Оса", GOSSIP_SENDER_MAIN, 93);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_warpstalker:30|t Прыгуана", GOSSIP_SENDER_MAIN, 94);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_netherray:30|t Скат пустоты", GOSSIP_SENDER_MAIN, 95);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_sporebat:30|t Спороскат", GOSSIP_SENDER_MAIN, 96);
			player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Achievement_BG_returnXflags_def_WSG:30:|t Назад", GOSSIP_SENDER_MAIN, 100);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;

		case 50:
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_chimera:30|t Химера", GOSSIP_SENDER_MAIN, 51);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_corehound:30|t Гончая Недр", GOSSIP_SENDER_MAIN, 52);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_devilsaur:30|t Дьявозавр", GOSSIP_SENDER_MAIN, 53);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/Ability_Hunter_Pet_Rhino:30|t Люторог", GOSSIP_SENDER_MAIN, 54);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_silithid:30|t Силитид", GOSSIP_SENDER_MAIN, 55);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_hunter_pet_worm:30|t Червь", GOSSIP_SENDER_MAIN, 56);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_druid_primalprecision:30|t Локе'нахак", GOSSIP_SENDER_MAIN, 57);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_druid_primalprecision:30|t Сколл", GOSSIP_SENDER_MAIN, 58);
			player->ADD_GOSSIP_ITEM(6, "|TInterface/ICONS/ability_druid_primalprecision:30|t Дух зверя.", GOSSIP_SENDER_MAIN, 59);
			player->ADD_GOSSIP_ITEM(4, "|TInterface/ICONS/Achievement_BG_returnXflags_def_WSG:30:|t Назад", GOSSIP_SENDER_MAIN, 100);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;

		// Credits to Serifaz who helped me with these ID's.
		case 51: // Химера
			CreatePet(player, creature, 21879);
			break;

		case 52: // Гончая Недр
			CreatePet(player, creature, 21108);
			break;

		case 53: // Дьявозавр
			CreatePet(player, creature, 20931);
			break;

		case 54: // Люторог
			CreatePet(player, creature, 30445);
			break;

		case 55: // Silithid
			CreatePet(player, creature, 5460);
			break;

		case 56: // Worm
			CreatePet(player, creature, 30148);
			break;

		case 57: // Loque'nahak
			CreatePet(player, creature, 32517);
			break;

		case 58: // Skoll
			CreatePet(player, creature, 35189);
			break;

		case 59: // Gondria
			CreatePet(player, creature, 33776);
			break;

		case 16: // Spider
			CreatePet(player, creature, 2349);
			break;

		case 17: // Dragonhawk
			CreatePet(player, creature, 27946);
			break;

		case 18: // Bat
			CreatePet(player, creature, 28233);
			break;

		case 19: // Ravager
			CreatePet(player, creature, 17199);
			break;

		case 20: // Raptor
			CreatePet(player, creature, 14821);
			break;

		case 21: // Serpent
			CreatePet(player, creature, 28358);
			break;

		case 1: // Bear
			CreatePet(player, creature, 29319);
			break;

		case 2: // Boar
			CreatePet(player, creature, 29996);
			break;

		case 93: // Bug
			CreatePet(player, creature, 28085);
			break;

		case 4: // Cat
			CreatePet(player, creature, 28097);
			break;

		case 5: // Carrion
			CreatePet(player, creature, 26838);
			break;

		case 6: // Crab
			CreatePet(player, creature, 24478);
			break;

		case 7: // Crocolisk
			CreatePet(player, creature, 1417);
			break;

		case 8: // Gorila
			CreatePet(player, creature, 28213);
			break;

		case 9: // Hound
			CreatePet(player, creature, 29452);
			break;

		case 10: // Hyena
			CreatePet(player, creature, 13036);
			break;

		case 11: // Moth
			CreatePet(player, creature, 27421);
			break;

		case 12: // Owl
			CreatePet(player, creature, 23136);
			break;

		case 13: // Strider
			CreatePet(player, creature, 22807);
			break;

		case 414: // Scorpid
			CreatePet(player, creature, 9698);
			break;

		case 15: // Turtle
			CreatePet(player, creature, 25482);
			break;

		case 94: // Прыгуана
			CreatePet(player, creature, 18464);
			break;

		case 95: // Скат пустоты
			CreatePet(player, creature, 18880);
			break;

		case 96: // Скат пустоты
			CreatePet(player, creature, 17724);
			break;
		}

		return true;
	}
};

uint32 weapon_war[] = {1180, 196, 201, 198, 197, 202, 199, 200, 227, 2567, 5011, 264};
uint32 weapon_pal[] = {196, 201, 198, 197, 202, 199, 200};
uint32 weapon_mage[] = {1180, 201, 227, 5009};
uint32 weapon_dk[] = {196, 201, 198, 197, 202, 199, 200};
uint32 weapon_druid[] = {198, 199, 200, 227};
uint32 weapon_shaman[] = {1180, 196, 198, 197, 199, 227};
uint32 weapon_hunter[] = {1180, 196, 201, 197, 202, 200, 227, 2567, 5011, 264};
uint32 weapon_rogue[] = {196, 201, 198, 2567, 5011, 264};
uint32 weapon_priest[] = {1180, 198, 227, 5009};
uint32 weapon_warlock[] = {1180, 201, 227, 5009};

static const size_t size_weapon_war = sizeof(weapon_war) / sizeof(*weapon_war);
static const size_t size_weapon_pal = sizeof(weapon_pal) / sizeof(*weapon_pal);
static const size_t size_weapon_mage = sizeof(weapon_mage) / sizeof(*weapon_mage);
static const size_t size_weapon_dk = sizeof(weapon_dk) / sizeof(*weapon_dk);
static const size_t size_weapon_druid = sizeof(weapon_druid) / sizeof(*weapon_druid);
static const size_t size_weapon_shaman = sizeof(weapon_shaman) / sizeof(*weapon_shaman);
static const size_t size_weapon_hunter = sizeof(weapon_hunter) / sizeof(*weapon_hunter);
static const size_t size_weapon_rogue = sizeof(weapon_rogue) / sizeof(*weapon_rogue);
static const size_t size_weapon_priest = sizeof(weapon_priest) / sizeof(*weapon_priest);
static const size_t size_weapon_warlock = sizeof(weapon_warlock) / sizeof(*weapon_warlock);

class npc_welcome : public CreatureScript
{
  public:
	npc_welcome() : CreatureScript("npc_welcome") {}

	bool OnGossipHello(Player *player, Creature *creature)
	{
		if (player->getLevel() >= 80)
		{
			{
				player->PrepareQuestMenu(creature->GetGUID());
				player->SendPreparedQuest(creature->GetGUID());
			}
			if (player->getClass() == CLASS_WARRIOR)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ClassIcon_Warrior:30|t Пройти обучение война", GOSSIP_SENDER_MAIN, MENU_WARRIOR);
			}
			if (player->getClass() == CLASS_PALADIN)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ClassIcon_Paladin:30|t Пройти обучение паладина", GOSSIP_SENDER_MAIN, MENU_PALADIN);
			}
			if (player->getClass() == CLASS_HUNTER)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ClassIcon_Hunter:30|t Пройти обучение охотника", GOSSIP_SENDER_MAIN, MENU_HUNTER);
			}
			if (player->getClass() == CLASS_ROGUE)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ClassIcon_Rogue:30|t Пройти обучение разбойника", GOSSIP_SENDER_MAIN, MENU_ROGUE);
			}
			if (player->getClass() == CLASS_PRIEST)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ClassIcon_Priest:30|t Пройти обучение жреца", GOSSIP_SENDER_MAIN, MENU_PRIEST);
			}
			if (player->getClass() == CLASS_DEATH_KNIGHT)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ClassIcon_DeathKnight:30|t Пройти обучение рыцаря смерти", GOSSIP_SENDER_MAIN, MENU_DEATH_K);
			}
			if (player->getClass() == CLASS_SHAMAN)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ClassIcon_Shaman:30|t Пройти обучение шамана", GOSSIP_SENDER_MAIN, MENU_SHAMAN);
			}
			if (player->getClass() == CLASS_MAGE)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ClassIcon_Mage:30|t Пройти обучение мага", GOSSIP_SENDER_MAIN, MENU_MAGE);
			}
			if (player->getClass() == CLASS_WARLOCK)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ClassIcon_Warlock:30|t Пройти обучение чернокнижника", GOSSIP_SENDER_MAIN, MENU_WARLOCK);
			}
			if (player->getClass() == CLASS_DRUID)
			{
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ClassIcon_Druid:30|t Пройти обучение друида", GOSSIP_SENDER_MAIN, MENU_DRUID);
			}

			player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ability_rogue_dirtydeeds:30|t Меню талантов", GOSSIP_SENDER_MAIN, OPTION_MENU_ID_1);
			player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/ability_rogue_dirtydeeds:30|t Изучение владения оружием", GOSSIP_SENDER_MAIN, 100);
			player->ADD_GOSSIP_ITEM(TRAINER_ICON, "|TInterface/ICONS/Ability_Mount_FelDrake:30|t Изучить верховую езду", GOSSIP_SENDER_MAIN, OPTION_MENU_ID_2);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		}
		else
		{
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
	{
		WorldSession *PGS = player->GetSession();

		player->PlayerTalkClass->ClearMenus();
		{
			//	/**//////////////////////////////////////////////////////////
			switch (action)
			{
			// Изучение оружия
			case 100:
				if (player->getClass() == CLASS_WARRIOR)
				{
					for (int i = 0; i < size_weapon_war; i++)
						player->learnSpell(weapon_war[i]);
				}
				if (player->getClass() == CLASS_PALADIN)
				{
					for (int i = 0; i < size_weapon_pal; i++)
						player->learnSpell(weapon_pal[i]);
				}
				if (player->getClass() == CLASS_HUNTER)
				{
					for (int i = 0; i < size_weapon_hunter; i++)
						player->learnSpell(weapon_hunter[i]);
				}
				if (player->getClass() == CLASS_ROGUE)
				{
					for (int i = 0; i < size_weapon_rogue; i++)
						player->learnSpell(weapon_rogue[i]);
				}
				if (player->getClass() == CLASS_PRIEST)
				{
					for (int i = 0; i < size_weapon_priest; i++)
						player->learnSpell(weapon_priest[i]);
				}
				if (player->getClass() == CLASS_DEATH_KNIGHT)
				{
					for (int i = 0; i < size_weapon_dk; i++)
						player->learnSpell(weapon_dk[i]);
				}
				if (player->getClass() == CLASS_SHAMAN)
				{
					for (int i = 0; i < size_weapon_shaman; i++)
						player->learnSpell(weapon_shaman[i]);
				}
				if (player->getClass() == CLASS_MAGE)
				{
					for (int i = 0; i < size_weapon_mage; i++)
						player->learnSpell(weapon_mage[i]);
				}
				if (player->getClass() == CLASS_WARLOCK)
				{
					for (int i = 0; i < size_weapon_warlock; i++)
						player->learnSpell(weapon_warlock[i]);
				}
				if (player->getClass() == CLASS_DRUID)
				{
					for (int i = 0; i < size_weapon_druid; i++)
						player->learnSpell(weapon_druid[i]);
				}
				player->SaveToDB(false, false);
				player->UpdateSkillsToMaxSkillsForLevel();
				player->CLOSE_GOSSIP_MENU();
				break;

			//=============================================WARRIOR=================================================//
			case MENU_WARRIOR:
				player->learnSpell(war_spell_Overpower),
					player->learnSpell(war_spell_Battle_Shout),
					player->learnSpell(war_spell_Heroic_Strike),
					player->learnSpell(war_spell_Charge),
					player->learnSpell(war_spell_Rend),
					player->learnSpell(war_spell_Thunder_Clap),
					player->learnSpell(war_spell_Victory_Rush),
					player->learnSpell(war_spell_Hamstring),
					player->learnSpell(war_spell_Bloodrage),
					player->learnSpell(war_spell_Defensive_Stance),
					player->learnSpell(war_spell_Sunder_Armor),
					player->learnSpell(war_spell_Taunt),
					player->learnSpell(war_spell_Shield_Bash),
					player->learnSpell(war_spell_Demoralizing_Shout),
					player->learnSpell(war_spell_Revenge),
					player->learnSpell(war_spell_Mocking_Blow),
					player->learnSpell(war_spell_Shield_Block),
					player->learnSpell(war_spell_Disarm),
					player->learnSpell(war_spell_Cleave),
					player->learnSpell(war_spell_Retaliation),
					player->learnSpell(war_spell_Stance_Mastery),
					player->learnSpell(war_spell_Execute),
					player->learnSpell(war_spell_Challenging_Shout),
					player->learnSpell(war_spell_Shield_Wall),
					player->learnSpell(war_spell_Berserker_Stance),
					player->learnSpell(war_spell_Intercept),
					player->learnSpell(war_spell_Slam),
					player->learnSpell(war_spell_Berserker_Rage),
					player->learnSpell(war_spell_Whirlwind),
					player->learnSpell(war_spell_Pummel),
					player->learnSpell(war_spell_Sheild_Slam),
					player->learnSpell(war_spell_Recklessness),
					player->learnSpell(war_spell_Spell_Reflection),
					player->learnSpell(war_spell_Commanding_Shout),
					player->learnSpell(war_spell_Intervene),
					player->learnSpell(war_spell_Shattering_Throw),
					player->learnSpell(war_spell_Enraged_Regeneration),
					player->learnSpell(war_spell_Heroic_Throw),
					player->learnSpell(war_spell_Dual_Wield),
					player->learnSpell(war_spell_Intimidating_Shout);
				player->learnSpell(war_spell_Parry);
				player->learnSpell(54197); // ?
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;
			//=============================================PALADIN=================================================//
			case MENU_PALADIN:
				player->learnSpell(pala_spell_Parry);
				player->learnSpell(pala_spell_Concentration_Aura);
				player->learnSpell(pala_spell_Divine_Intervention);
				player->learnSpell(pala_spell_Plate_Mail_skill);
				player->learnSpell(pala_spell_Devotion_Aura);
				player->learnSpell(pala_spell_Holy_Light);
				player->learnSpell(pala_spell_Blessing_of_Might);
				player->learnSpell(pala_spell_Judgement_of_Light);
				player->learnSpell(pala_spell_Divine_Protection);
				player->learnSpell(pala_spell_Hammer_of_Justice);
				player->learnSpell(pala_spell_Purify);
				player->learnSpell(pala_spell_Hand_of_Protection);
				player->learnSpell(pala_spell_Lay_on_Hands);
				player->learnSpell(pala_spell_Judgement_of_Wisdom);
				player->learnSpell(pala_spell_Redemption);
				player->learnSpell(pala_spell_Blessing_of_Wisdom);
				player->learnSpell(pala_spell_Righteous_Defense);
				player->learnSpell(pala_spell_Hand_of_Reckoning);
				player->learnSpell(pala_spell_Retribution_Aura);
				player->learnSpell(pala_spell_Righteous_Fury);
				player->learnSpell(pala_spell_Hand_of_Freedom);
				player->learnSpell(pala_spell_Blessing_of_Kings);
				player->learnSpell(pala_spell_Consecration);
				player->learnSpell(pala_spell_Exorcism);
				player->learnSpell(pala_spell_Flash_of_Light);
				player->learnSpell(pala_spell_Sense_Undead);
				player->learnSpell(pala_spell_Seal_of_Justice);
				player->learnSpell(pala_spell_Turn_Evil);
				player->learnSpell(pala_spell_Hand_of_Salvation);
				player->learnSpell(pala_spell_Judgement_of_Justice);
				player->learnSpell(pala_spell_Shadow_Resistance_Aura);
				player->learnSpell(pala_spell_Seal_of_Light);
				player->learnSpell(pala_spell_Frost_Resistance_Aura);
				player->learnSpell(pala_spell_Divine_Shield);
				player->learnSpell(pala_spell_Fire_Resistance_Aura);
				player->learnSpell(pala_spell_Seal_of_Wisdom);
				player->learnSpell(pala_spell_Cleanse);
				player->learnSpell(pala_spell_Hammer_of_Wrath);
				player->learnSpell(pala_spell_Hand_of_Sacrifice);
				player->learnSpell(pala_spell_Holy_Wrath);
				player->learnSpell(pala_spell_Greater_Blessing_of_Might);
				player->learnSpell(pala_spell_Greater_Blessing_of_Wisdom);
				player->learnSpell(pala_spell_Greater_Blessing_of_Kings);
				player->learnSpell(pala_spell_Crusader_Aura);
				player->learnSpell(pala_spell_Avenging_Wrath);
				player->learnSpell(pala_spell_Divine_Plea);
				player->learnSpell(pala_spell_Shield_of_Righteousness);
				player->learnSpell(pala_spell_Sacred_Shield);
				player->learnSpell(33388); //?
				player->learnSpell(33391); //?
				//Spell Learned for different factions..
				if (player->GetTeamId() == TEAM_ALLIANCE)
				{
					player->learnSpell(pala_spell_Seal_of_Vengeance);
					player->learnSpell(pala_spell_Warhorse);
					player->learnSpell(pala_spell_Charger);
				}
				else
				{
					player->learnSpell(pala_spell_Seal_of_Corruption);
					player->learnSpell(pala_spell_Thalassian_Warhorse);
					player->learnSpell(pala_spell_Thalassian_Charger);
				}
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;
			//=============================================HUNTER=================================================//
			case MENU_HUNTER:
				player->learnSpell(hunter_spell_Scorpid_Sting);
				player->learnSpell(hunter_spell_Parry);
				player->learnSpell(hunter_spell_Rapid_Fire);
				player->learnSpell(hunter_spell_Viper_Sting);
				player->learnSpell(hunter_spell_Track_Beasts);
				player->learnSpell(hunter_spell_Aspect_of_the_Monkey);
				player->learnSpell(hunter_spell_Raptor_Strike);
				player->learnSpell(hunter_spell_Serpent_Sting);
				player->learnSpell(hunter_spell_Arcane_Shot);
				player->learnSpell(hunter_spell_Hunters_Mark);
				player->learnSpell(hunter_spell_Concussive_Shot);
				player->learnSpell(hunter_spell_Aspect_of_the_Hawk);
				player->learnSpell(hunter_spell_Call_Pet);
				player->learnSpell(hunter_spell_Dismiss_Pet);
				player->learnSpell(hunter_spell_Feed_Pet);
				player->learnSpell(hunter_spell_Revive_Pet);
				player->learnSpell(hunter_spell_Tame_Beast);
				player->learnSpell(hunter_spell_Track_Humanoids);
				player->learnSpell(hunter_spell_Distracting_Shot);
				player->learnSpell(hunter_spell_Mend_Pet);
				player->learnSpell(hunter_spell_Wing_Clip);
				player->learnSpell(hunter_spell_Eagle_Eye);
				player->learnSpell(hunter_spell_Eyes_of_the_Beast);
				player->learnSpell(hunter_spell_Scare_Beast);
				player->learnSpell(hunter_spell_Aspect_of_the_Cheetah);
				player->learnSpell(hunter_spell_Immolation_Trap);
				player->learnSpell(hunter_spell_Mongoose_Bite);
				player->learnSpell(hunter_spell_Multi_Shot);
				player->learnSpell(hunter_spell_Track_Undead);
				player->learnSpell(hunter_spell_Aspect_of_the_Viper);
				player->learnSpell(hunter_spell_Disengage);
				player->learnSpell(hunter_spell_Freezing_Trap);
				player->learnSpell(hunter_spell_Beast_Lore);
				player->learnSpell(hunter_spell_Track_Hidden);
				player->learnSpell(hunter_spell_Track_Elementals);
				player->learnSpell(hunter_spell_Frost_Trap);
				player->learnSpell(hunter_spell_Aspect_of_the_Beast);
				player->learnSpell(hunter_spell_Feign_Death);
				player->learnSpell(hunter_spell_Flare);
				player->learnSpell(hunter_spell_Track_Demons);
				player->learnSpell(hunter_spell_Explosive_Trap);
				player->learnSpell(hunter_spell_Aspect_of_the_Pack);
				player->learnSpell(hunter_spell_Track_Giants);
				player->learnSpell(hunter_spell_Volley);
				player->learnSpell(hunter_spell_Aspect_of_the_Wild);
				player->learnSpell(hunter_spell_Steady_Shot);
				player->learnSpell(hunter_spell_Track_Dragonkin);
				player->learnSpell(hunter_spell_Deterrence);
				player->learnSpell(hunter_spell_Tranquilizing_Shot);
				player->learnSpell(hunter_spell_Kill_Command);
				player->learnSpell(hunter_spell_Snake_Trap);
				player->learnSpell(hunter_spell_Misdirection);
				player->learnSpell(hunter_spell_Kill_Shot);
				player->learnSpell(hunter_spell_Aspect_of_the_Dragonhawk);
				player->learnSpell(hunter_spell_Masters_Call);
				player->learnSpell(hunter_spell_Freezing_Arrow);
				player->learnSpell(hunter_spell_Call_Stabled_Pet);
				player->learnSpell(hunter_spell_Dual_Wield);
				player->learnSpell(8737); //?
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;
				//=============================================ROGUE=================================================//
			case MENU_ROGUE:
				player->learnSpell(rogue_spell_Parry);
				player->learnSpell(rogue_spell_Dual_Wield); //  ambi
				player->learnSpell(rogue_spell_Eviscerate);
				player->learnSpell(rogue_spell_Sinister_Strike);
				player->learnSpell(rogue_spell_Stealth);
				player->learnSpell(rogue_spell_Backstab);
				player->learnSpell(rogue_spell_Pick_Pocket);
				player->learnSpell(rogue_spell_Gouge);
				player->learnSpell(rogue_spell_Evasion);
				player->learnSpell(rogue_spell_Sap);
				player->learnSpell(rogue_spell_Slice_and_Dice);
				player->learnSpell(rogue_spell_Sprint);
				player->learnSpell(rogue_spell_Kick);
				player->learnSpell(rogue_spell_Garrote);
				player->learnSpell(rogue_spell_Feint);
				player->learnSpell(rogue_spell_Lockpicking_skill);
				player->learnSpell(rogue_spell_Expose_Armor);
				player->learnSpell(rogue_spell_Ambush);
				player->learnSpell(rogue_spell_Dismantle);
				player->learnSpell(rogue_spell_Rupture);
				player->learnSpell(rogue_spell_Distract);
				player->learnSpell(rogue_spell_Vanish);
				player->learnSpell(rogue_spell_Detect_Traps);
				player->learnSpell(rogue_spell_Cheap_Shot);
				player->learnSpell(rogue_spell_Disarm_Trap);
				player->learnSpell(rogue_spell_Kidney_Shot);
				player->learnSpell(rogue_spell_Blind);
				player->learnSpell(rogue_spell_Safe_Fall);
				player->learnSpell(rogue_spell_Envenom);
				player->learnSpell(rogue_spell_Deadly_Throw);
				player->learnSpell(rogue_spell_Cloak_of_Shadows);
				player->learnSpell(rogue_spell_Shiv);
				player->learnSpell(rogue_spell_Tricks_of_the_Trade);
				player->learnSpell(rogue_spell_Fan_of_Knives);
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;
			case MENU_PRIEST:
				player->learnSpell(priest_spell_Cure_Disease);
				player->learnSpell(priest_spell_Lesser_Heal);
				player->learnSpell(priest_spell_Power_Word_Fortitude);
				player->learnSpell(priest_spell_Smite);
				player->learnSpell(priest_spell_Shadow_Word_Pain);
				player->learnSpell(priest_spell_Power_Word_Shield);
				player->learnSpell(priest_spell_Fade);
				player->learnSpell(priest_spell_Renew);
				player->learnSpell(priest_spell_Mind_Blast);
				player->learnSpell(priest_spell_Resurrection);
				player->learnSpell(priest_spell_Inner_Fire);
				player->learnSpell(priest_spell_Psychic_Scream);
				player->learnSpell(priest_spell_Heal);
				player->learnSpell(priest_spell_Dispel_Magic);
				player->learnSpell(priest_spell_Devouring_Plague);
				player->learnSpell(priest_spell_Fear_Ward);
				player->learnSpell(priest_spell_Flash_Heal);
				player->learnSpell(priest_spell_Holy_Fire);
				player->learnSpell(priest_spell_Holy_Nova);
				player->learnSpell(priest_spell_Mind_Soothe);
				player->learnSpell(priest_spell_Shackle_Undead);
				player->learnSpell(priest_spell_Mind_Vision);
				player->learnSpell(priest_spell_Mana_Burn);
				player->learnSpell(priest_spell_Divine_Spirit);
				player->learnSpell(priest_spell_Mind_Control);
				player->learnSpell(priest_spell_Prayer_of_Healing);
				player->learnSpell(priest_spell_Shadow_Protection);
				player->learnSpell(priest_spell_Abolish_Disease);
				player->learnSpell(priest_spell_Levitate);
				player->learnSpell(priest_spell_Greater_Heal);
				player->learnSpell(priest_spell_Prayer_of_Fortitude);
				player->learnSpell(priest_spell_Prayer_of_Shadow_Protection);
				player->learnSpell(priest_spell_Prayer_of_Spirit);
				player->learnSpell(priest_spell_Shadow_Word_Death);
				player->learnSpell(priest_spell_Binding_Heal);
				player->learnSpell(priest_spell_Shadowfiend);
				player->learnSpell(priest_spell_Prayer_of_Mending);
				player->learnSpell(priest_spell_Mass_Dispel);
				player->learnSpell(priest_spell_Divine_Hymn);
				player->learnSpell(priest_spell_Hymn_of_Hope);
				player->learnSpell(priest_spell_Mind_Sear);
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;
				//=============================================DEATH KNGIHTS=================================================//
			case MENU_DEATH_K:
				player->learnSpell(dk_spell_Parry);
				player->learnSpell(dk_spell_Pestilence);
				player->learnSpell(dk_spell_Blood_Boil);
				player->learnSpell(dk_spell_Blood_Strike);
				player->learnSpell(dk_spell_Strangulate);
				player->learnSpell(dk_spell_Blood_Tap);
				player->learnSpell(dk_spell_Path_of_Frost);
				player->learnSpell(dk_spell_Dark_Command);
				player->learnSpell(dk_spell_Death_Pact);
				player->learnSpell(dk_spell_Frost_Presence);
				player->learnSpell(dk_spell_Icy_Touch);
				player->learnSpell(dk_spell_Mind_Freeze);
				player->learnSpell(dk_spell_Chains_of_Ice);
				player->learnSpell(dk_spell_Icebound_Fortitude);
				player->learnSpell(dk_spell_Horn_of_Winter);
				player->learnSpell(dk_spell_Rune_Strike);
				player->learnSpell(dk_spell_Empower_Rune_Weapon);
				player->learnSpell(dk_spell_Death_Coil);
				player->learnSpell(dk_spell_Death_Gate);
				player->learnSpell(dk_spell_Plague_Strike);
				player->learnSpell(dk_spell_Death_Grip);
				player->learnSpell(dk_spell_Raise_Dead);
				player->learnSpell(dk_spell_Death_and_Decay);
				player->learnSpell(dk_spell_Anti_Magic_Shell);
				player->learnSpell(dk_spell_Unholy_Presence);
				player->learnSpell(dk_spell_Raise_Ally);
				player->learnSpell(dk_spell_Army_of_the_Dead);
				player->learnSpell(dk_spell_Runeforging_skill);
				player->learnSpell(dk_spell_Acherus_Deathcharger);
				player->learnSpell(dk_spell_Obliterate);
				player->learnSpell(dk_spell_Death_Strike);
				player->learnSpell(war_spell_Dual_Wield);
				//================RuneForge================//
				player->learnSpell(dk_spell_Uknowas);
				player->learnSpell(dk_spell_Uknowah);
				player->learnSpell(dk_spell_Uknowai);
				player->learnSpell(dk_spell_Uknowaz);
				player->learnSpell(dk_spell_Uknowan);
				player->learnSpell(dk_spell_Uknowab);
				player->learnSpell(dk_spell_Uknowav);
				player->learnSpell(dk_spell_Uknowaj);
				player->learnSpell(dk_spell_Uknowaq);
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;
				//=============================================SHAMAN=================================================//
			case MENU_SHAMAN:
				player->learnSpell(8737); //?
				player->learnSpell(shaman_spell_Earth_Elemental_Totem);
				player->learnSpell(shaman_spell_Healing_Wave);
				player->learnSpell(shaman_spell_Lightning_Bolt);
				player->learnSpell(shaman_spell_Rockbiter_Weapon);
				player->learnSpell(shaman_spell_Earth_Shock);
				player->learnSpell(shaman_spell_Stoneskin_Totem);
				player->learnSpell(shaman_spell_Earthbind_Totem);
				player->learnSpell(shaman_spell_Lightning_Shield);
				player->learnSpell(shaman_spell_Stoneclaw_Totem);
				player->learnSpell(shaman_spell_Flame_Shock);
				player->learnSpell(shaman_spell_Flametongue_Weapon);
				player->learnSpell(shaman_spell_Searing_Totem);
				player->learnSpell(shaman_spell_Strength_of_Earth_Totem);
				player->learnSpell(shaman_spell_Ancestral_Spirit);
				player->learnSpell(shaman_spell_Fire_Nova);
				player->learnSpell(shaman_spell_Purge);
				player->learnSpell(shaman_spell_Cure_Toxins);
				player->learnSpell(shaman_spell_Ghost_Wolf);
				player->learnSpell(shaman_spell_Wind_Shear);
				player->learnSpell(shaman_spell_Tremor_Totem);
				player->learnSpell(shaman_spell_Frost_Shock);
				player->learnSpell(shaman_spell_Frostbrand_Weapon);
				player->learnSpell(shaman_spell_Healing_Stream_Totem);
				player->learnSpell(shaman_spell_Lesser_Healing_Wave);
				player->learnSpell(shaman_spell_Water_Shield);
				player->learnSpell(shaman_spell_Water_Breathing);
				player->learnSpell(shaman_spell_Frost_Resistance_Totem);
				player->learnSpell(shaman_spell_Far_Sight);
				player->learnSpell(shaman_spell_Magma_Totem);
				player->learnSpell(shaman_spell_Mana_Spring_Totem);
				player->learnSpell(shaman_spell_Fire_Resistance_Totem);
				player->learnSpell(shaman_spell_Flametongue_Totem);
				player->learnSpell(shaman_spell_Water_Walking);
				player->learnSpell(shaman_spell_Astral_Recall);
				player->learnSpell(shaman_spell_Call_of_the_Elements);
				player->learnSpell(shaman_spell_Earthliving_Weapon);
				player->learnSpell(shaman_spell_Grounding_Totem);
				player->learnSpell(shaman_spell_Nature_Resistance_Totem);
				player->learnSpell(shaman_spell_Reincarnation);
				player->learnSpell(shaman_spell_Totemic_Recall);
				player->learnSpell(shaman_spell_Windfury_Weapon);
				player->learnSpell(shaman_spell_Chain_Lightning);
				player->learnSpell(shaman_spell_Windfury_Totem);
				player->learnSpell(shaman_spell_Sentry_Totem);
				player->learnSpell(shaman_spell_Cleansing_Totem);
				player->learnSpell(shaman_spell_Call_of_the_Ancestors);
				player->learnSpell(shaman_spell_Chain_Heal);
				player->learnSpell(shaman_spell_Call_of_the_Spirits);
				player->learnSpell(shaman_spell_Wrath_of_Air_Totem);
				player->learnSpell(shaman_spell_Fire_Elemental_Totem);
				player->learnSpell(shaman_spell_Lava_Burst);
				player->learnSpell(shaman_spell_Hex);

				if (player->GetTeamId() == TEAM_ALLIANCE)
					player->learnSpell(shaman_spell_Heroism);
				else
					player->learnSpell(shaman_spell_Bloodlust);

				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;
				//=============================================MAGE=================================================//
			case MENU_MAGE:
				player->learnSpell(mage_spell_Arcane_Explosion);
				player->learnSpell(mage_spell_Frostbolt);
				player->learnSpell(mage_spell_Arcane_Intellect);
				player->learnSpell(mage_spell_Fireball);
				player->learnSpell(mage_spell_Conjure_Water);
				player->learnSpell(mage_spell_Conjure_Food);
				player->learnSpell(mage_spell_Fire_Blast);
				player->learnSpell(mage_spell_Arcane_Missiles);
				player->learnSpell(mage_spell_Polymorph);
				player->learnSpell(mage_spell_Polymorph_Turtle);
				player->learnSpell(mage_spell_Polymorph_Turkey);
				player->learnSpell(mage_spell_Polymorph_Rabbit);
				player->learnSpell(mage_spell_Polymorph_Pig);
				player->learnSpell(mage_spell_Frost_Nova);
				player->learnSpell(mage_spell_Dampen_Magic);
				player->learnSpell(mage_spell_Slow_Fall);
				player->learnSpell(mage_spell_Flamestrike);
				player->learnSpell(mage_spell_Amplify_Magic);
				player->learnSpell(mage_spell_Remove_Curse);
				player->learnSpell(mage_spell_Blink);
				player->learnSpell(mage_spell_Blizzard);
				player->learnSpell(mage_spell_Evocation);
				player->learnSpell(mage_spell_Fire_Ward);
				player->learnSpell(mage_spell_Mana_Shield);
				player->learnSpell(mage_spell_Frost_Ward);
				player->learnSpell(mage_spell_Scorch);
				player->learnSpell(mage_spell_Counterspell);
				player->learnSpell(mage_spell_Cone_of_Cold);
				player->learnSpell(mage_spell_Conjure_Mana_Gem);
				player->learnSpell(mage_spell_Ice_Armor);
				player->learnSpell(mage_spell_Ice_Block);
				player->learnSpell(mage_spell_Mage_Armor);
				player->learnSpell(mage_spell_Arcane_Brilliance);
				player->learnSpell(mage_spell_Molten_Armor);
				player->learnSpell(mage_spell_Arcane_Blast);
				player->learnSpell(mage_spell_Ice_Lance);
				player->learnSpell(mage_spell_Invisibility);
				player->learnSpell(mage_spell_Ritual_of_Refreshment);
				player->learnSpell(mage_spell_Spellsteal);
				player->learnSpell(mage_spell_Conjure_Refreshment);
				player->learnSpell(mage_spell_Frostfire_Bolt);
				player->learnSpell(mage_spell_Dalaran_Brilliance);
				player->learnSpell(mage_spell_Dalaran_Intellect);
				player->learnSpell(mage_spell_Mirror_Image);
				player->learnSpell(mage_spell_Portal_Dalaran);
				player->learnSpell(mage_spell_Frost_Armor);
				player->learnSpell(61305); //?
				player->SaveToDB(false, false);
				/////////RESTRICTION/////////////
				if (player->GetTeamId() == TEAM_ALLIANCE)
				{
					player->learnSpell(mage_spell_Teleport_Exodar);
					player->learnSpell(mage_spell_Teleport_Theramore);
					player->learnSpell(mage_spell_Teleport_Darnassus);
					player->learnSpell(mage_spell_Teleport_Shattrath);
					player->learnSpell(mage_spell_Teleport_Ironforge);
					player->learnSpell(mage_spell_Teleport_Stromwind);
					player->learnSpell(mage_spell_Portal_Darnassus);
					player->learnSpell(mage_spell_Portal_Exodar);
					player->learnSpell(mage_spell_Portal_Ironforge);
					player->learnSpell(mage_spell_Portal_Shattrath);
					player->learnSpell(mage_spell_Portal_Theramore);
				}
				else
				{
					player->learnSpell(mage_spell_Teleport_Orgrimmar);
					player->learnSpell(mage_spell_Teleport_Shattrath_H);
					player->learnSpell(mage_spell_Teleport_Thunder_Bluff);
					player->learnSpell(mage_spell_Teleport_Stonard);
					player->learnSpell(mage_spell_Teleport_Silvermoon);
					player->learnSpell(mage_spell_Teleport_Undercity);
					player->learnSpell(mage_spell_Portal_Orgrimmar);
					player->learnSpell(mage_spell_Portal_Shattrath_H);
					player->learnSpell(mage_spell_Portal_Silvermoon);
					player->learnSpell(mage_spell_Portal_Stonard);
					player->learnSpell(mage_spell_Portal_Thunder_Bluff);
					player->learnSpell(mage_spell_Portal_Undercity);
				}
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;
			//=============================================WARLOCK=================================================//
			case MENU_WARLOCK:
				player->learnSpell(warlock_spell_Demon_Skin);
				player->learnSpell(warlock_spell_Immolate);
				player->learnSpell(warlock_spell_Shadow_Bolt);
				player->learnSpell(warlock_spell_Summon_Imp);
				player->learnSpell(warlock_spell_Corruption);
				player->learnSpell(warlock_spell_Curse_of_Weakness);
				player->learnSpell(warlock_spell_Life_Tap);
				player->learnSpell(warlock_spell_Curse_of_Agony);
				player->learnSpell(warlock_spell_Fear);
				player->learnSpell(warlock_spell_Create_Healthstone);
				player->learnSpell(warlock_spell_Drain_Soul);
				player->learnSpell(warlock_spell_Summon_Voidwalker);
				player->learnSpell(warlock_spell_Health_Funnel);
				player->learnSpell(warlock_spell_Drain_Life);
				player->learnSpell(warlock_spell_Unending_Breath);
				player->learnSpell(warlock_spell_Create_Soulstone);
				player->learnSpell(warlock_spell_Searing_Pain);
				player->learnSpell(warlock_spell_Demon_Armor);
				player->learnSpell(warlock_spell_Rain_of_Fire);
				player->learnSpell(warlock_spell_Ritual_of_Summoning);
				player->learnSpell(warlock_spell_Summon_Succubus);
				player->learnSpell(warlock_spell_Eye_of_Kilrogg);
				player->learnSpell(warlock_spell_Drain_Mana);
				player->learnSpell(warlock_spell_Sense_Demons);
				player->learnSpell(warlock_spell_Curse_of_Tongues);
				player->learnSpell(warlock_spell_Detect_Invisibility);
				player->learnSpell(warlock_spell_Create_Firestone);
				player->learnSpell(warlock_spell_Banish);
				player->learnSpell(warlock_spell_Enslave_Demon);
				player->learnSpell(warlock_spell_Hellfire);
				player->learnSpell(warlock_spell_Summon_Felhunter);
				player->learnSpell(warlock_spell_Curse_of_the_Elements);
				player->learnSpell(warlock_spell_Shadow_Ward);
				player->learnSpell(warlock_spell_Create_Spellstone);
				player->learnSpell(warlock_spell_Howl_of_Terror);
				player->learnSpell(warlock_spell_Death_Coil);
				player->learnSpell(warlock_spell_Soul_Fire);
				player->learnSpell(warlock_spell_Inferno);
				player->learnSpell(warlock_spell_Curse_of_Doom);
				player->learnSpell(warlock_spell_Ritual_of_Doom);
				player->learnSpell(warlock_spell_Fel_Armor);
				player->learnSpell(warlock_spell_Incinerate);
				player->learnSpell(warlock_spell_Soulshatter);
				player->learnSpell(warlock_spell_Ritual_of_Souls);
				player->learnSpell(warlock_spell_Seed_of_Corruption);
				player->learnSpell(warlock_spell_Shadowflame);
				player->learnSpell(warlock_spell_Demonic_Circle_Summon);
				player->learnSpell(warlock_spell_Demonic_Circle_Teleport);
				player->learnSpell(warlock_spell_Dreadsteed);
				player->learnSpell(33388); //?
				player->learnSpell(33391); //?
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;
				//=============================================DRUID=================================================//
			case MENU_DRUID:
				if (player->getClass() == CLASS_DRUID)
				{
					player->learnSpell(druid_spell_Healing_Touch);
					player->learnSpell(druid_spell_Mark_of_the_Wild);
					player->learnSpell(druid_spell_Wrath);
					player->learnSpell(druid_spell_Moonfire);
					player->learnSpell(druid_spell_Rejuvenation);
					player->learnSpell(druid_spell_Thorns);
					player->learnSpell(druid_spell_Entangling_Roots);
					player->learnSpell(druid_spell_Bear_Form);
					player->learnSpell(druid_spell_Demoralizing_Roar);
					player->learnSpell(druid_spell_Growl);
					player->learnSpell(druid_spell_Maul);
					player->learnSpell(druid_spell_Natures_Grasp);
					player->learnSpell(druid_spell_Teleport_Moonglade);
					player->learnSpell(druid_spell_Enrage);
					player->learnSpell(druid_spell_Regrowth);
					player->learnSpell(druid_spell_Revive);
					player->learnSpell(druid_spell_Bash);
					player->learnSpell(druid_spell_Cure_Poison);
					player->learnSpell(druid_spell_Aquatic_Form);
					player->learnSpell(druid_spell_Swipe_Bear);
					player->learnSpell(druid_spell_Travel_Form);
					player->learnSpell(druid_spell_Faerie_Fire);
					player->learnSpell(druid_spell_Faerie_Fire_Feral);
					player->learnSpell(druid_spell_Hibernate);
					player->learnSpell(druid_spell_Cat_Form);
					//	player->learnSpell(druid_spell_Feral_Charge_Bear); // charge farouche 2
					//	player->learnSpell(druid_spell_Feral_Charge_Cat); // charge farouche
					player->learnSpell(druid_spell_Prowl);
					player->learnSpell(druid_spell_Rebirth);
					player->learnSpell(druid_spell_Rip);
					player->learnSpell(druid_spell_Starfire);
					player->learnSpell(druid_spell_Shred);
					player->learnSpell(druid_spell_Soothe_Animal);
					player->learnSpell(druid_spell_Rake);
					player->learnSpell(druid_spell_Remove_Curse);
					player->learnSpell(druid_spell_Tigers_Fury);
					player->learnSpell(druid_spell_Abolish_Poison);
					player->learnSpell(druid_spell_Dash);
					player->learnSpell(druid_spell_Challenging_Roar);
					player->learnSpell(druid_spell_Cower);
					player->learnSpell(druid_spell_Tranquility);
					player->learnSpell(druid_spell_Ferocious_Bite);
					player->learnSpell(druid_spell_Ravage);
					player->learnSpell(druid_spell_Track_Humanoids);
					player->learnSpell(druid_spell_Frenzied_Regeneration);
					player->learnSpell(druid_spell_Pounce);
					player->learnSpell(druid_spell_Dire_Bear_Form);
					player->learnSpell(druid_spell_Feline_Grace);
					player->learnSpell(druid_spell_Hurricane);
					player->learnSpell(druid_spell_Innervate);
					player->learnSpell(druid_spell_Savage_Defense);
					player->learnSpell(druid_spell_Barkskin);
					player->learnSpell(druid_spell_Gift_of_the_Wild);
					//	player->learnSpell(druid_spell_Mangle_Bear); mutilation farouche 2
					//	player->learnSpell(druid_spell_Mangle_Cat); mutilation farouche
					player->learnSpell(druid_spell_Flight_Form);
					player->learnSpell(druid_spell_Maim);
					player->learnSpell(druid_spell_Lifebloom);
					player->learnSpell(druid_spell_Lacerate);
					player->learnSpell(druid_spell_Cyclone);
					player->learnSpell(druid_spell_Swift_Flight_Form);
					player->learnSpell(druid_spell_Swipe_Cat);
					player->learnSpell(druid_spell_Savage_Roar);
					player->learnSpell(druid_spell_Nourish);
					player->learnSpell(druid_spell_Claw);
					player->learnSpell(druid_spell_Claw_1);
				}
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;

			case OPTION_MENU_ID_1:
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, SUB_MENU_TALENT_OPTION_1, GOSSIP_SENDER_MAIN, SUB_OPTION_MENU_ID_1);
				player->ADD_GOSSIP_ITEM(TRAINER_ICON, SUB_MENU_TALENT_OPTION_2, GOSSIP_SENDER_MAIN, SUB_OPTION_MENU_ID_2);
				player->ADD_GOSSIP_ITEM(CHAT_ICON, back, GOSSIP_SENDER_MAIN, BACK_OPTION_MENU_1);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case SUB_OPTION_MENU_ID_1:
				player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
				player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());
				//=====WARRIOR TALENT=====//
				//Arms
				if (player->HasSpell(12294)) //Mortal Strike Rank 1
				{
					player->learnSpell(war_spell_Mortal_Strike);
				}
				//Prot
				if (player->HasSpell(20243)) //Devastate Rank 1
				{
					player->learnSpell(war_spell_Devastate);
				}
				//=====PALADIN TALENT=====//
				//Holy
				if (player->HasSpell(20925)) //Holy Shield Rank 1
				{
					player->learnSpell(pala_spell_Holy_Shield);
				}
				if (player->HasSpell(20473)) //Holy Shock Rank 1
				{
					player->learnSpell(pala_spell_Holy_Shock);
				}
				//Prot
				if (player->HasSpell(31935)) //Avengers Shield Rank 1
				{
					player->learnSpell(pala_spell_Avengers_Shield);
				}
				if (player->HasSpell(20911)) //Blessing of Sanctuary Rank 1
				{
					player->learnSpell(pala_spell_Greater_Blessing_of_Sanctuary);
				}
				//=====HUNTER  TALENT=====//
				//Survival
				if (player->HasSpell(19386)) //Wyvern String Rank 1
				{
					player->learnSpell(hunter_spell_Wyvern_Sting);
				}
				if (player->HasSpell(53301)) //Explosive Shot Rank 1
				{
					player->learnSpell(hunter_spell_Explosive_Shot);
				}
				if (player->HasSpell(19306)) //Conter Attack Rank 1
				{
					player->learnSpell(hunter_spell_Conterattack);
				}
				//Marksmanship
				if (player->HasSpell(19434)) //Aimed Shot Rank 1
				{
					player->learnSpell(hunter_spell_Aimed_Shot);
				}
				//=====ROGUE   TALENT=====//
				//Subtlety
				if (player->HasSpell(16511)) //Hemorrhage Rank 1
				{
					player->learnSpell(rogue_spell_Hemorrhage);
				}
				//Assassination
				if (player->HasSpell(1329)) //Mutilate Rank 1
				{
					player->learnSpell(rogue_spell_Mutilate);
				}
				//=====PRIEST  TALENT=====//
				//Shadow
				if (player->HasSpell(34914)) //Vampiric Touch Rank 1
				{
					player->learnSpell(priest_spell_Vampiric_Touch);
				}
				//Discipline
				if (player->HasSpell(47540)) //Penance Rank 1
				{
					player->learnSpell(priest_spell_Penance);
				}
				//Holy
				if (player->HasSpell(724)) //LightWell Rank 1
				{
					player->learnSpell(priest_spell_Lightwell);
				}
				if (player->HasSpell(19236)) //Desperate Prayer Rank 1
				{
					player->learnSpell(priest_spell_Desperate_Prayer);
				}
				if (player->HasSpell(34861)) //Circle Of healing Rank 1
				{
					player->learnSpell(priest_spell_Circle_of_Healing);
				}
				//Shadow
				if (player->HasSpell(15407)) //Mind Flay Rank 1
				{
					player->learnSpell(priest_spell_Mind_Flay);
				}
				//=====DEATH_K TALENT=====//
				//Blood
				if (player->HasSpell(55050)) //Heart Strike Rank 1
				{
					player->learnSpell(dk_spell_Heart_Strike);
				}
				//Frost
				if (player->HasSpell(49143)) //Frost Strike Rank 1
				{
					player->learnSpell(dk_spell_Frost_Strike);
				}
				if (player->HasSpell(49184)) //Howling Blast Rank 1
				{
					player->learnSpell(dk_spell_Howling_Blast);
				}
				//UnHoly
				if (player->HasSpell(55090)) //Scourge Strike Rank 1
				{
					player->learnSpell(dk_spell_Scourge_Strike);
				}
				if (player->HasSpell(49158)) //Corpse Explosion Rank 1
				{
					player->learnSpell(dk_spell_Corpse_Explosion);
				}
				//=====SHAMAN  TALENT=====//
				//Restoration
				if (player->HasSpell(61295)) //Riptide Rank 1
				{
					player->learnSpell(shaman_spell_Riptide);
				}
				if (player->HasSpell(974)) //Earth Shield Rank 1
				{
					player->learnSpell(shaman_spell_Earth_Shield);
				}
				//Elemental
				if (player->HasSpell(30706)) //Totem of Wrath Rank 1
				{
					player->learnSpell(shaman_spell_Totem_of_Wrath);
				}
				if (player->HasSpell(51490)) //TunderStorm Rank 1
				{
					player->learnSpell(shaman_spell_Thunderstorm);
				}
				//=====MAGE    TALENT=====//
				//Arcane
				if (player->HasSpell(44425)) //Arcane Barrage Rank 1
				{
					player->learnSpell(mage_spell_Arcane_Barrage);
				}
				//Fire
				if (player->HasSpell(11113)) //Blast Wave Rank 1
				{
					player->learnSpell(mage_spell_Blast_Wave);
				}
				if (player->HasSpell(31661)) //Dragon Breath  Rank 1
				{
					player->learnSpell(mage_spell_Dragons_Breath);
				}
				if (player->HasSpell(44457)) //Living Bomb Rank 1
				{
					player->learnSpell(mage_spell_Living_Bomb);
				}
				if (player->HasSpell(11366)) //Pyroblast Rank 1
				{
					player->learnSpell(mage_spell_Pyroblast);
				}
				//Frost
				if (player->HasSpell(11426)) //Ice Barrier Rank 1
				{
					player->learnSpell(mage_spell_Ice_Barrier);
				}
				//=====WARLOCK TALENT=====//
				//Destruction
				if (player->HasSpell(17877)) //ShadowBurn Rank 1
				{
					player->learnSpell(warlock_spell_Shadowburn);
				}
				if (player->HasSpell(30283)) //ShadowFury Rank 1
				{
					player->learnSpell(warlock_spell_Shadowfury);
				}
				if (player->HasSpell(50796)) //Chaos Bolt Rank 1
				{
					player->learnSpell(warlock_spell_Chaos_Bolt);
				}
				//Affliction
				if (player->HasSpell(30108)) //Unstable Affliction Rank 1
				{
					player->learnSpell(warlock_spell_Unstable_Affliction);
				}
				if (player->HasSpell(48181)) //Spell Haunt Rank 1
				{
					player->learnSpell(warlock_spell_Haunt);
				}
				if (player->HasSpell(18220)) //Dark Pact Rank 1
				{
					player->learnSpell(warlock_spell_Dark_Pact);
				}
				//=====DRUID   TALENT=====//
				//Balance
				if (player->HasSpell(50516)) //Typhoon Rank 1
				{
					player->learnSpell(druid_spell_Typhoon);
				}
				if (player->HasSpell(48505)) //Starfall Rank 1
				{
					player->learnSpell(druid_spell_Starfall);
				}
				if (player->HasSpell(5570)) //Insect Swarm Rank 1
				{
					player->learnSpell(druid_spell_Insect_Swarm);
				}
				//Restoration
				if (player->HasSpell(48438)) //Wild Growth Rank 1
				{
					player->learnSpell(druid_spell_Wild_Growth);
				}
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;

			case SUB_OPTION_MENU_ID_2:
				player->resetTalents(true);
				player->SendTalentsInfoData(false);
				player->GetSession()->SendNotification("Ваши таланты были сброшены!");
				player->SaveToDB(false, false);
				player->CLOSE_GOSSIP_MENU();
				break;

			case OPTION_MENU_ID_2:
				player->CastSpell(player, 34093, true, NULL, NULL, player->GetGUID());
				if (player->HasSpell(42777))
				{
					player->CLOSE_GOSSIP_MENU();
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->learnSpell(42777);
				}
				player->CLOSE_GOSSIP_MENU();
				break;

			case BACK_OPTION_MENU_1: //Main Menu
				OnGossipHello(player, creature);
				break;
			}
		}
		return true;
	}
};

class Professions_NPC_Test : public CreatureScript
{
  public:
	  Professions_NPC_Test() : CreatureScript("Professions_NPC_Test") {}

	void static CreatureWhisperBasedOnBool(const char *text, Creature *_creature, Player *Player, bool value)
	{
		if (value)
			_creature->MonsterWhisper(text, Player, false);
	}

	uint32 PlayerMaxLevel() const
	{
		return sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
	}

	static bool PlayerHasItemOrSpell(const Player *plr, uint32 itemId, uint32 spellId)
	{
		return plr->HasItemCount(itemId, 1, true) || plr->HasSpell(spellId);
	}

	bool OnGossipHello(Player *Player, Creature *_creature)
	{
		if (sConfigMgr->GetBoolDefault("Unell.NPC.Professions.OnlyVIP", true) && !Player->GetSession()->IsPremium())
		{
			_creature->MonsterWhisper("Я могу помочь только VIP игрокам...", Player, false);
			Player->CLOSE_GOSSIP_MENU();
			return false;
		}

		Player->ADD_GOSSIP_ITEM(9, "[Профессии] ->", GOSSIP_SENDER_MAIN, 196);
		Player->PlayerTalkClass->SendGossipMenu(907, _creature->GetGUID());
		return true;
	}

	static bool PlayerAlreadyHasTwoProfessions(const Player *Player)
	{
		uint32 skillCount = 0;

		if (Player->HasSkill(SKILL_MINING))
			skillCount++;
		if (Player->HasSkill(SKILL_SKINNING))
			skillCount++;
		if (Player->HasSkill(SKILL_HERBALISM))
			skillCount++;

		if (skillCount >= 2)
			return true;

		for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
		{
			SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
			if (!SkillInfo)
				continue;

			if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
				continue;

			if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
				continue;

			const uint32 skillID = SkillInfo->id;

			if (Player->HasSkill(skillID))
				skillCount++;

			if (skillCount >= 2)
				return true;
		}
		return false;
	}

	static bool LearnAllRecipesInProfession(Player *Player, SkillType skill)
	{
		ChatHandler handler(Player->GetSession());
		char *skill_name;
		SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
		skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];
		LearnSkillRecipesHelper(Player, SkillInfo->id);
		Player->SetSkill(SkillInfo->id, Player->GetSkillStep(SkillInfo->id), 450, 450);
		handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);
		return true;
	}

	static void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
	{
		uint32 classmask = player->getClassMask();

		for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
		{
			SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
			if (!skillLine)
				continue;

			// wrong skill
			if (skillLine->skillId != skill_id)
				continue;

			// not high rank
			if (skillLine->forward_spellid)
				continue;

			// skip racial skills
			if (skillLine->racemask != 0)
				continue;

			// skip wrong class skills
			if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
				continue;

			SpellInfo const *spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
			if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo))
				continue;

			player->learnSpell(skillLine->spellId);
		}
	}

	static bool IsSecondarySkill(SkillType skill)
	{
		return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
	}

	void static CompleteLearnProfession(Player *Player, Creature *pCreature, SkillType skill)
	{
		if (PlayerAlreadyHasTwoProfessions(Player) && !IsSecondarySkill(skill))
			pCreature->MonsterWhisper("Больше 2-ух професси иметь нельзя!", Player, false);
		else
		{
			if (!LearnAllRecipesInProfession(Player, skill))
				pCreature->MonsterWhisper("Internal error occured!", Player, false);
		}
	}

	bool OnGossipSelect(Player *player, Creature *_creature, uint32 uiSender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();

		if (uiSender == GOSSIP_SENDER_MAIN)
		{
			switch (uiAction)
			{
			case 196:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_alchemy:30|t Алхимия.", GOSSIP_SENDER_MAIN, 1);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Ingot_05:30|t Кузнечное дело.", GOSSIP_SENDER_MAIN, 2);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Misc_LeatherScrap_02:30|t Кожевничество.", GOSSIP_SENDER_MAIN, 3);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Fabric_Felcloth_Ebon:30|t Портняжное дело.", GOSSIP_SENDER_MAIN, 4);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_wrench_01:30|t Инженерное дело.", GOSSIP_SENDER_MAIN, 5);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_engraving:30|t Наложение чар.", GOSSIP_SENDER_MAIN, 6);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_gem_01:30|t Ювелирное дело.", GOSSIP_SENDER_MAIN, 7);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Scroll_08:30|t Начертание.", GOSSIP_SENDER_MAIN, 8);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Misc_Herb_07:30|t Травничество.", GOSSIP_SENDER_MAIN, 9);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_pelt_wolf_01:30|t Снятие шкур.", GOSSIP_SENDER_MAIN, 10);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_mining:30|t Горное дело.", GOSSIP_SENDER_MAIN, 11);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_fishing:30|t Рыболовное дело.", GOSSIP_SENDER_MAIN, 13);
				player->PlayerTalkClass->SendGossipMenu(1, _creature->GetGUID());
				break;
			
			case 1:
				if (player->HasSkill(SKILL_ALCHEMY))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}

				CompleteLearnProfession(player, _creature, SKILL_ALCHEMY);

				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 2:
				if (player->HasSkill(SKILL_BLACKSMITHING))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}
				CompleteLearnProfession(player, _creature, SKILL_BLACKSMITHING);

				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 3:
				if (player->HasSkill(SKILL_LEATHERWORKING))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}
				CompleteLearnProfession(player, _creature, SKILL_LEATHERWORKING);

				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 4:
				if (player->HasSkill(SKILL_TAILORING))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}
				CompleteLearnProfession(player, _creature, SKILL_TAILORING);

				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 5:
				if (player->HasSkill(SKILL_ENGINEERING))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}
				CompleteLearnProfession(player, _creature, SKILL_ENGINEERING);

				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 6:
				if (player->HasSkill(SKILL_ENCHANTING))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}
				CompleteLearnProfession(player, _creature, SKILL_ENCHANTING);

				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 7:
				if (player->HasSkill(SKILL_JEWELCRAFTING))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}
				CompleteLearnProfession(player, _creature, SKILL_JEWELCRAFTING);

				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 8:
				if (player->HasSkill(SKILL_INSCRIPTION))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}
				CompleteLearnProfession(player, _creature, SKILL_INSCRIPTION);

				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 9:
				if (player->HasSkill(SKILL_HERBALISM))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}

				CompleteLearnProfession(player, _creature, SKILL_HERBALISM);
				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 10:
				if (player->HasSkill(SKILL_SKINNING))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}

				CompleteLearnProfession(player, _creature, SKILL_SKINNING);
				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 11:
				if (player->HasSkill(SKILL_MINING))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}

				CompleteLearnProfession(player, _creature, SKILL_MINING);
				player->CLOSE_GOSSIP_MENU();
				break;
			
			case 12:
				player->CLOSE_GOSSIP_MENU();
				break;

			case 13:
				if (player->HasSkill(SKILL_FISHING))
				{
					player->CLOSE_GOSSIP_MENU();
					break;
				}

				CompleteLearnProfession(player, _creature, SKILL_FISHING);
				player->CLOSE_GOSSIP_MENU();
				break;
			}
		}
		return true;
	}
};

class Unell_Lottery : public CreatureScript
{
  public:
	Unell_Lottery() : CreatureScript("Unell_Lottery") {}

	bool OnGossipHello(Player *player, Creature *creature)
	{
		player->ADD_GOSSIP_ITEM(10, "Ну всё, хочу всё про*бать!!!", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(10, "Test", GOSSIP_SENDER_MAIN, 2);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		if (sender != GOSSIP_SENDER_MAIN)
			return true; // wrong sender, something fisy

		switch (action)
		{
		// case 1: ChatHandler(player->GetSession()).PSendSysMessage("123");
		case 1:
			player->CLOSE_GOSSIP_MENU(); // Shattered Sun Magi
			player->AddItem(44113, 1);
			break;

			break;

			return true; // invalid class, something fishy
		}

		return true;
	}
};

class Unell_Prize_OBT : public CreatureScript
{
  public:
	Unell_Prize_OBT() : CreatureScript("Unell_Prize_OBT") {}

	bool OnGossipHello(Player *player, Creature *creature)
	{
		ChatHandler handler(player->GetSession());

		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(10, "Информация", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(10, "Получить награду", GOSSIP_SENDER_MAIN, 2);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 uiSender, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		ChatHandler handler(player->GetSession());
		uint32 accid = player->GetSession()->GetAccountId();
		uint32 dateOBT = sConfigMgr->GetIntDefault("Unell.OBT.Prize.Date", 1504213200);
		uint32 viptime = sConfigMgr->GetIntDefault("Unell.OBT.Prize.Vip.Time", 2592000);
		time_t curTime = time(NULL);
		uint32 localtime = curTime;
		uint32 totaltime = localtime + viptime; // unsettime вооот

		switch (action)
		{
		case 1: // Инфа
			player->CLOSE_GOSSIP_MENU();
			handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Перед вами нпц для выдачи наград, для тех кто помогал администрации тестировать игровой мир");
			handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Данный нпц выдаёт награды тому, кто был зарегистрирован, когда сервер находился в режиме ОБТ");
			break;

		case 2: // Получение плюшки
			player->CLOSE_GOSSIP_MENU();
			{
				// SELECT UNIX_TIMESTAMP(joindate) from account where id = 2;
				QueryResult res = LoginDatabase.PQuery("SELECT UNIX_TIMESTAMP(joindate) FROM account WHERE id = %u", accid);
				if (res)
				{
					uint32 joindate = res->Fetch()->GetUInt32();

					QueryResult resdate = LoginDatabase.PQuery("SELECT FROM_UNIXTIME(%u)", dateOBT);
					std::string resdateOBT = resdate->Fetch()->GetCString();

					QueryResult resdatejoin = LoginDatabase.PQuery("SELECT FROM_UNIXTIME(%u)", joindate);
					std::string datejoin = resdatejoin->Fetch()->GetCString();

					QueryResult resacc = LoginDatabase.PQuery("SELECT account FROM `prize_obt` WHERE `account` = '%u' ", accid);

					if (resacc)
					{
						handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Вы уже получали награду. Она выдаётся только один раз, увы...");
					}

					if (!resacc)
					{
						if (joindate > dateOBT)
							handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Ваш аккаунт зарегистрирован пожже: |cffff0000%s|cff00ff00. Следовательно, вы не могли быть на ОБТ", resdateOBT.c_str());
						else
						{
							handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Ваш аккаунт зарегистрирован: |cffff0000%s|cff00ff00. Следовательно, вы могли быть на ОБТ", datejoin.c_str());
							handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Поэтому вы получаете награду от администрации. Приятной игры.");
							LoginDatabase.PExecute("INSERT INTO `prize_obt` (`account`, `date`) VALUES ('%u', %u)", accid, localtime);

							if (!player->GetSession()->IsPremium())
								LoginDatabase.PExecute("INSERT INTO `account_premium` (`id`, `setdate`, `unsetdate`, `premium_type`, `active`) VALUES ('%u', '%u', '%u', '1', '1');", accid, localtime, totaltime);
							else
								LoginDatabase.PExecute("UPDATE `account_premium` SET `unsetdate`=`unsetdate`+%u WHERE (`id`='%u');", viptime, accid);

							ChatHandler(player->GetSession()).PSendSysMessage("|cFFFF0000#|cff6C8CD5 Вы получили доступ к VIP аккаунту, пожалуйста, перезайдите в игру полностью");

							CharTitlesEntry const *titleInfo = sCharTitlesStore.LookupEntry(180);
							if (!titleInfo)
								return false;

							player->SetTitle(titleInfo); // to be sure that title now known
						}
					}
				}
				if (!res)
					handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Проблемы с аккаунтом о.о");
			}
			break;
		}
		return true;
	}
};

class Unell_Prize_NewYear : public CreatureScript
{
  public:
	Unell_Prize_NewYear() : CreatureScript("Unell_Prize_NewYear") {}

	bool OnGossipHello(Player *player, Creature *creature)
	{
		ChatHandler handler(player->GetSession());

		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(10, "Информация", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(10, "Получить награду", GOSSIP_SENDER_MAIN, 2);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 uiSender, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		ChatHandler handler(player->GetSession());
		uint32 accid = player->GetSession()->GetAccountId();
		uint32 date_31 = sConfigMgr->GetIntDefault("Unell.New.Year.Prize.Date.31", 1514678400);
		uint32 date_2 = sConfigMgr->GetIntDefault("Unell.New.Year.Prize.Date.2", 1514851200);
		uint32 count_ice = sConfigMgr->GetIntDefault("Unell.New.Year.Prize.Count.Ice", 100);
		uint32 item_mount = sConfigMgr->GetIntDefault("Unell.New.Year.Prize.ItemID.Mount", 32768);
		uint32 count_honor = sConfigMgr->GetIntDefault("Unell.New.Year.Prize.Honor", 100000);
		uint32 count_cron = sConfigMgr->GetIntDefault("Unell.New.Year.Prize.Cron.Count", 200);
		time_t curTime = time(NULL);
		uint32 localtime = curTime;

		switch (action)
		{
		case 1: // Инфа	о нг
			player->CLOSE_GOSSIP_MENU();
			handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Перед вами нпц для выдачи наград, который выдаёт награды только 31 декабря и 1 января.");
			handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Награда выдаётся только один раз на один аккаунт.");
			break;

		case 2: // Получение плюшки
			player->CLOSE_GOSSIP_MENU();
			{
				if (localtime < date_31 || localtime > date_2)
					handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 В данный момент уже нельзя получить награду");
				else
				{
					QueryResult resacc = UnellDatabase.PQuery("SELECT account FROM `prize_new_year` WHERE `account` = '%u' ", accid);
					if (resacc)
					{
						handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Вы уже получали награду. Она выдаётся только один раз, увы...");
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 Администрация сервера поздравляет вас с новым 2018 годом.");
						handler.PSendSysMessage("|cFFFF0000#|r|cff00ff00 А так же дарит вам эти подарки. Приятной игры.");
						UnellDatabase.PExecute("INSERT INTO `prize_new_year` (`account`, `date`) VALUES ('%u', %u)", accid, localtime);

						player->AddItem(49426, count_ice);
						player->AddItem(item_mount, 1);
						player->ModifyHonorPoints(count_honor);
						player->AddItem(120000, count_cron);
					}
				}
			}
			break;
		}
		return true;
	}
};

class npc_enchantment_private : public CreatureScript
{
  public:
	npc_enchantment_private() : CreatureScript("npc_enchantment_private") {}

	bool OnGossipHello(Player *player, Creature *creature)
	{
		if (sConfigMgr->GetBoolDefault("Unell.NPC.Enchantment.OnlyVIP", true) && !player->GetSession()->IsPremium())
		{
			creature->MonsterWhisper("Я могу помочь только VIP игрокам...", player, false);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}

		player->ADD_GOSSIP_ITEM(1, "Зачарить Правую руку", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Левую руку", GOSSIP_SENDER_MAIN, 13);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Двуручное Оружие", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Щит", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Голову", GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Плечи", GOSSIP_SENDER_MAIN, 5);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Спину", GOSSIP_SENDER_MAIN, 6);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Грудь", GOSSIP_SENDER_MAIN, 7);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Запястья", GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Руки", GOSSIP_SENDER_MAIN, 9);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Ноги", GOSSIP_SENDER_MAIN, 10);
		player->ADD_GOSSIP_ITEM(1, "Зачарить Ступни", GOSSIP_SENDER_MAIN, 11);

		if (player->HasSkill(SKILL_ENCHANTING) && player->GetSkillValue(SKILL_ENCHANTING) > 400)
		{
			player->ADD_GOSSIP_ITEM(1, "Зачарить Кольцо # 1", GOSSIP_SENDER_MAIN, 12);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Кольцо # 2", GOSSIP_SENDER_MAIN, 1200);
		}
		player->ADD_GOSSIP_ITEM(1, "Я хотел бы снять мои чары", GOSSIP_SENDER_MAIN, 14);

		player->PlayerTalkClass->SendGossipMenu(100001, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		Item *item;

		switch (action)
		{

		case 1: // Enchant Weapon
			if (player->HasSkill(SKILL_ENCHANTING) && player->GetSkillValue(SKILL_ENCHANTING) > 400)
			{
				player->ADD_GOSSIP_ITEM(1, "Отведение удара", GOSSIP_SENDER_MAIN, 102);
				player->ADD_GOSSIP_ITEM(1, "Вытягивание крови", GOSSIP_SENDER_MAIN, 103);
			}
			player->ADD_GOSSIP_ITEM(1, "+ 26 к ловкости", GOSSIP_SENDER_MAIN, 100);
			player->ADD_GOSSIP_ITEM(1, "+ 45 к духу", GOSSIP_SENDER_MAIN, 101);
			player->ADD_GOSSIP_ITEM(1, "Боевое исступление", GOSSIP_SENDER_MAIN, 104);
			player->ADD_GOSSIP_ITEM(1, "+ 25 к меткости и + 25 к крит. удару", GOSSIP_SENDER_MAIN, 105);
			player->ADD_GOSSIP_ITEM(1, "Чёрная магия", GOSSIP_SENDER_MAIN, 106);
			player->ADD_GOSSIP_ITEM(1, "Военачальник", GOSSIP_SENDER_MAIN, 107);
			player->ADD_GOSSIP_ITEM(1, "Оружие Ледомола", GOSSIP_SENDER_MAIN, 108);
			player->ADD_GOSSIP_ITEM(1, "Оберег", GOSSIP_SENDER_MAIN, 109);
			player->ADD_GOSSIP_ITEM(1, "+ 50 к выносливости", GOSSIP_SENDER_MAIN, 110);
			player->ADD_GOSSIP_ITEM(1, "+ 65 к силе атаки", GOSSIP_SENDER_MAIN, 111);
			player->ADD_GOSSIP_ITEM(1, "+ 63 к силе заклинаний", GOSSIP_SENDER_MAIN, 112);
			player->ADD_GOSSIP_ITEM(1, "Мангуст", GOSSIP_SENDER_MAIN, 113);
			player->ADD_GOSSIP_ITEM(1, "Палач", GOSSIP_SENDER_MAIN, 114);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100002, creature->GetGUID());
			return true;
			break;

		case 2: // Enchant 2H Weapon
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

			if (!item)
			{
				player->GetSession()->SendNotification("Сначала нужно одеть двуручное оружие!");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
			{
				player->ADD_GOSSIP_ITEM(1, "Боевое исступление", GOSSIP_SENDER_MAIN, 104);
				player->ADD_GOSSIP_ITEM(1, "+ 81 к силе заклинаний", GOSSIP_SENDER_MAIN, 115);
				player->ADD_GOSSIP_ITEM(1, "+ 35 к ловкости", GOSSIP_SENDER_MAIN, 116);
				player->ADD_GOSSIP_ITEM(1, "+ 110 к силе атаки", GOSSIP_SENDER_MAIN, 117);
				player->ADD_GOSSIP_ITEM(1, "Мангуст", GOSSIP_SENDER_MAIN, 113);
				player->ADD_GOSSIP_ITEM(1, "Палач", GOSSIP_SENDER_MAIN, 114);
				player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
				player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
				return true;
			}
			else
			{
				player->GetSession()->SendNotification("У вас не одето двуручное оружие!");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 3: // Enchant Shield
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendNotification("Сначала нужно одеть щит!");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				player->ADD_GOSSIP_ITEM(1, "+ 20 к рейтингу защиты", GOSSIP_SENDER_MAIN, 118);
				player->ADD_GOSSIP_ITEM(1, "+ 25 к интеллекту", GOSSIP_SENDER_MAIN, 119);
				player->ADD_GOSSIP_ITEM(1, "+ 12 к рейтингу устойчивости", GOSSIP_SENDER_MAIN, 120);
				player->ADD_GOSSIP_ITEM(1, "Титановая обшивка", GOSSIP_SENDER_MAIN, 121);
				player->ADD_GOSSIP_ITEM(1, "+ 18 к выносливости", GOSSIP_SENDER_MAIN, 122);
				player->ADD_GOSSIP_ITEM(1, "+ 36 к блокированию", GOSSIP_SENDER_MAIN, 123);
				player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
				player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
				return true;
			}
			else
			{
				player->GetSession()->SendNotification("У вас не одет щит!");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 4: // Enchant Head
			player->ADD_GOSSIP_ITEM(1, "+ 30 к силе заклинаний и + 10 ед. маны каждые 5 сек", GOSSIP_SENDER_MAIN, 124);
			player->ADD_GOSSIP_ITEM(1, "+ 30 к силе заклинаний и + 20 к крит. удару ", GOSSIP_SENDER_MAIN, 125);
			player->ADD_GOSSIP_ITEM(1, "+ 29 к силе заклинаний и + 20 к устойчивости", GOSSIP_SENDER_MAIN, 126);
			player->ADD_GOSSIP_ITEM(1, "+ 30 к выносливости и + 25 к устойчивости", GOSSIP_SENDER_MAIN, 127);
			player->ADD_GOSSIP_ITEM(1, "+ 37 к выносливости и + 20 к защите", GOSSIP_SENDER_MAIN, 128);
			player->ADD_GOSSIP_ITEM(1, "+ 50 к силе атаки и + 20 к крит. удару", GOSSIP_SENDER_MAIN, 129);
			player->ADD_GOSSIP_ITEM(1, "+ 50 к силе атаки и + 20 к устойчивости", GOSSIP_SENDER_MAIN, 130);
			player->ADD_GOSSIP_ITEM(1, "+ 25 к сопр. тайной магии и + 30 к выносливости", GOSSIP_SENDER_MAIN, 131);
			player->ADD_GOSSIP_ITEM(1, "+ 25 к сопр. огню и + 30 к выносливости", GOSSIP_SENDER_MAIN, 132);
			player->ADD_GOSSIP_ITEM(1, "+ 25 к сопр. тёмной магии и + 30 к выносливости", GOSSIP_SENDER_MAIN, 133);
			player->ADD_GOSSIP_ITEM(1, "+ 25 к сопр. магии льда и + 30 к выносливости", GOSSIP_SENDER_MAIN, 134);
			player->ADD_GOSSIP_ITEM(1, "+ 25 к сопр. силы природы и + 30 к выносливости", GOSSIP_SENDER_MAIN, 135);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100005, creature->GetGUID());
			return true;
			break;

		case 5: // Enchant Shoulders
			if (player->HasSkill(SKILL_INSCRIPTION) && player->GetSkillValue(SKILL_INSCRIPTION) > 400)
			{
				player->ADD_GOSSIP_ITEM(1, "+ 120 к силе атаки и + 15 к крит. удару", GOSSIP_SENDER_MAIN, 136);
				player->ADD_GOSSIP_ITEM(1, "+ 70 к силе заклинаний и + 8 ед. маны каждые 5 сек", GOSSIP_SENDER_MAIN, 137);
				player->ADD_GOSSIP_ITEM(1, "+ 60 к рейтингу уклонения и + 15 к защите", GOSSIP_SENDER_MAIN, 138);
				player->ADD_GOSSIP_ITEM(1, "+ 70 к силе заклинаний и + 15 к крит. эффекта", GOSSIP_SENDER_MAIN, 139);
			}
			player->ADD_GOSSIP_ITEM(1, "+ 40 к силе атаки и + 15 к крит. удару", GOSSIP_SENDER_MAIN, 140);
			player->ADD_GOSSIP_ITEM(1, "+ 24 к силе заклинаний и + 8 ед. маны каждые 5 сек", GOSSIP_SENDER_MAIN, 141);
			player->ADD_GOSSIP_ITEM(1, "+ 30 к выносливости и + 15 к устойчивости", GOSSIP_SENDER_MAIN, 142);
			player->ADD_GOSSIP_ITEM(1, "+ 20 к рейтингу уклонения и + 15 к защите", GOSSIP_SENDER_MAIN, 143);
			player->ADD_GOSSIP_ITEM(1, "+ 24 к силе заклинаний и + 15 к крит. удара", GOSSIP_SENDER_MAIN, 144);
			player->ADD_GOSSIP_ITEM(1, "+ 23 к силе заклинаний и + 15 к устойчивости", GOSSIP_SENDER_MAIN, 145);
			player->ADD_GOSSIP_ITEM(1, "+ 40 к силе атаки и + 15 к устойчивости", GOSSIP_SENDER_MAIN, 146);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100006, creature->GetGUID());
			return true;
			break;

		case 6: // Enchant Cloak
			player->ADD_GOSSIP_ITEM(1, "Уменьшение скорости падения", GOSSIP_SENDER_MAIN, 147);
			player->ADD_GOSSIP_ITEM(1, "Улучшенная незаметность + 10 к ловкости", GOSSIP_SENDER_MAIN, 148);
			player->ADD_GOSSIP_ITEM(1, "Вышивка тёмного сияния", GOSSIP_SENDER_MAIN, 149);
			player->ADD_GOSSIP_ITEM(1, "Светлотканная вышивка", GOSSIP_SENDER_MAIN, 150);
			player->ADD_GOSSIP_ITEM(1, "Вышивка в виде рукояти меча", GOSSIP_SENDER_MAIN, 151);
			player->ADD_GOSSIP_ITEM(1, "+ 10 к духу и снижение угрозы на 2%", GOSSIP_SENDER_MAIN, 152);
			player->ADD_GOSSIP_ITEM(1, "+ 16 к защите", GOSSIP_SENDER_MAIN, 153);
			player->ADD_GOSSIP_ITEM(1, "+ 35 к проникающей способности заклинаний", GOSSIP_SENDER_MAIN, 154);
			player->ADD_GOSSIP_ITEM(1, "+ 225 к броне", GOSSIP_SENDER_MAIN, 155);
			player->ADD_GOSSIP_ITEM(1, "+ 22 к ловкости", GOSSIP_SENDER_MAIN, 156);
			player->ADD_GOSSIP_ITEM(1, "+ 23 к скорости", GOSSIP_SENDER_MAIN, 157);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100007, creature->GetGUID());
			return true;
			break;

		case 7: //Enchant chest
			player->ADD_GOSSIP_ITEM(1, "+ 10 ко всему", GOSSIP_SENDER_MAIN, 158);
			player->ADD_GOSSIP_ITEM(1, "+ 275 к здоровью", GOSSIP_SENDER_MAIN, 159);
			player->ADD_GOSSIP_ITEM(1, "+ 10 ед. маны каждые 5 сек", GOSSIP_SENDER_MAIN, 160);
			player->ADD_GOSSIP_ITEM(1, "+ 20 к устойчивости", GOSSIP_SENDER_MAIN, 161);
			player->ADD_GOSSIP_ITEM(1, "+ 22 к защите", GOSSIP_SENDER_MAIN, 162);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100008, creature->GetGUID());
			return true;
			break;

		case 8: //Enchant Bracers
			player->ADD_GOSSIP_ITEM(1, "+ 40 к выносливости", GOSSIP_SENDER_MAIN, 163);
			player->ADD_GOSSIP_ITEM(1, "+ 30 к силе заклинаний", GOSSIP_SENDER_MAIN, 164);
			player->ADD_GOSSIP_ITEM(1, "+ 50 к силе атаки", GOSSIP_SENDER_MAIN, 165);
			player->ADD_GOSSIP_ITEM(1, "+ 18 к духу", GOSSIP_SENDER_MAIN, 166);
			player->ADD_GOSSIP_ITEM(1, "+ 15 к мастерству", GOSSIP_SENDER_MAIN, 167);
			player->ADD_GOSSIP_ITEM(1, "+ 6 ко всему", GOSSIP_SENDER_MAIN, 168);
			player->ADD_GOSSIP_ITEM(1, "+ 16 к интеллекту", GOSSIP_SENDER_MAIN, 169);
			player->ADD_GOSSIP_ITEM(1, "+ 70 к сопротивлению тайной магии", GOSSIP_SENDER_MAIN, 170);
			player->ADD_GOSSIP_ITEM(1, "+ 70 к сопротивлению магии огня", GOSSIP_SENDER_MAIN, 171);
			player->ADD_GOSSIP_ITEM(1, "+ 70 к сопротивлению магии льда", GOSSIP_SENDER_MAIN, 172);
			player->ADD_GOSSIP_ITEM(1, "+ 70 к сопротивлению силам природы", GOSSIP_SENDER_MAIN, 173);
			player->ADD_GOSSIP_ITEM(1, "+ 70 к сопротивлению тёмной магии", GOSSIP_SENDER_MAIN, 174);
			player->ADD_GOSSIP_ITEM(1, "+ 130 к силе атаки", GOSSIP_SENDER_MAIN, 175);
			player->ADD_GOSSIP_ITEM(1, "+ 102 к выносливости", GOSSIP_SENDER_MAIN, 176);
			player->ADD_GOSSIP_ITEM(1, "+ 76 к силе заклинаний", GOSSIP_SENDER_MAIN, 177);
			//player->ADD_GOSSIP_ITEM(1, "+ Гнездо в наручах", GOSSIP_SENDER_MAIN, 414);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100009, creature->GetGUID());
			return true;
			break;

		case 9: //Enchant Gloves
			player->ADD_GOSSIP_ITEM(1, "+ 16 к крит. удару", GOSSIP_SENDER_MAIN, 178);
			player->ADD_GOSSIP_ITEM(1, "+ 2% угрозы и + 10 к паррированию", GOSSIP_SENDER_MAIN, 179);
			player->ADD_GOSSIP_ITEM(1, "+ 44 к силе атаки", GOSSIP_SENDER_MAIN, 180);
			player->ADD_GOSSIP_ITEM(1, "+ 20 к ловкости", GOSSIP_SENDER_MAIN, 181);
			player->ADD_GOSSIP_ITEM(1, "+ 20 к меткости", GOSSIP_SENDER_MAIN, 182);
			player->ADD_GOSSIP_ITEM(1, "+ 15 к мастерству", GOSSIP_SENDER_MAIN, 183);
			player->ADD_GOSSIP_ITEM(1, "Выстрел ракетой", GOSSIP_SENDER_MAIN, 199);
			// player->ADD_GOSSIP_ITEM(1, "+ Гнездо в перчатках", GOSSIP_SENDER_MAIN, 415);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100010, creature->GetGUID());
			return true;
			break;

		case 10: //Enchant legs
			player->ADD_GOSSIP_ITEM(1, "+ 40 к устойчивости и + 28 к выносливости", GOSSIP_SENDER_MAIN, 184);
			player->ADD_GOSSIP_ITEM(1, "+ 55 к выносливости и + 22 к ловкости", GOSSIP_SENDER_MAIN, 185);
			player->ADD_GOSSIP_ITEM(1, "+ 75 к силе атаки и + 22 к крит. удару", GOSSIP_SENDER_MAIN, 186);
			player->ADD_GOSSIP_ITEM(1, "+ 50 к силе заклинаний + 20 к духу", GOSSIP_SENDER_MAIN, 187);
			player->ADD_GOSSIP_ITEM(1, "+ 50 к силе заклинаний + 30 к выносливости", GOSSIP_SENDER_MAIN, 188);
			player->ADD_GOSSIP_ITEM(1, "+ 72 к выносливости + 35 к ловкости", GOSSIP_SENDER_MAIN, 189);
			player->ADD_GOSSIP_ITEM(1, "+ 100 к силе атаки и + 36 к крит. удару", GOSSIP_SENDER_MAIN, 190);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100011, creature->GetGUID());
			return true;
			break;

		case 11: //Enchant feet
			player->ADD_GOSSIP_ITEM(1, "+ 32 к силе атаки", GOSSIP_SENDER_MAIN, 191);
			player->ADD_GOSSIP_ITEM(1, "+ 15 к выносливости и ув. скорости бега", GOSSIP_SENDER_MAIN, 192);
			player->ADD_GOSSIP_ITEM(1, "+ 16 к ловкости", GOSSIP_SENDER_MAIN, 193);
			player->ADD_GOSSIP_ITEM(1, "+ 18 к духу", GOSSIP_SENDER_MAIN, 194);
			player->ADD_GOSSIP_ITEM(1, "+ 7 ед. здоровья и маны каждые 5 сек.", GOSSIP_SENDER_MAIN, 195);
			player->ADD_GOSSIP_ITEM(1, "+ 12 к рейтингу меткости + 12 к крит. удару", GOSSIP_SENDER_MAIN, 196);
			player->ADD_GOSSIP_ITEM(1, "+ 22  к выносливости", GOSSIP_SENDER_MAIN, 197);
			player->ADD_GOSSIP_ITEM(1, "Нитроускоритель", GOSSIP_SENDER_MAIN, 198);
			player->ADD_GOSSIP_ITEM(1, "Рейтинг скорости + 340 на 12 сек", GOSSIP_SENDER_MAIN, 200);
			player->ADD_GOSSIP_ITEM(1, "+ 885 к броне", GOSSIP_SENDER_MAIN, 201);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100012, creature->GetGUID());
			return true;
			break;

		case 12: //Enchant rings
			player->ADD_GOSSIP_ITEM(1, "+ 40 к силе атаки", GOSSIP_SENDER_MAIN, 202);
			player->ADD_GOSSIP_ITEM(1, "+ 23 к силе заклинаний", GOSSIP_SENDER_MAIN, 203);
			player->ADD_GOSSIP_ITEM(1, "+ 30 к выносливости", GOSSIP_SENDER_MAIN, 204);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100013, creature->GetGUID());
			return true;
			break;

		case 1200: //Enchant rings
			player->ADD_GOSSIP_ITEM(1, "+ 40 к силе атаки", GOSSIP_SENDER_MAIN, 2022);
			player->ADD_GOSSIP_ITEM(1, "+ 23 к силе заклинаний", GOSSIP_SENDER_MAIN, 2032);
			player->ADD_GOSSIP_ITEM(1, "+ 30 к выносливости", GOSSIP_SENDER_MAIN, 2042);
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100013, creature->GetGUID());
			return true;
			break;

		case 13: //Enchant Off-Hand weapons
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendNotification("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				player->ADD_GOSSIP_ITEM(1, "Отведение удара", GOSSIP_SENDER_MAIN, 205);
				player->ADD_GOSSIP_ITEM(1, "Вытягивание крови", GOSSIP_SENDER_MAIN, 219);
				player->ADD_GOSSIP_ITEM(1, "+ 26 к ловкости", GOSSIP_SENDER_MAIN, 206);
				player->ADD_GOSSIP_ITEM(1, "+ 45 к духу", GOSSIP_SENDER_MAIN, 207);
				player->ADD_GOSSIP_ITEM(1, "Боевое исступление", GOSSIP_SENDER_MAIN, 208);
				player->ADD_GOSSIP_ITEM(1, "+ 25 к меткости и + 25 к крит. удару", GOSSIP_SENDER_MAIN, 209);
				player->ADD_GOSSIP_ITEM(1, "Чёрная магия", GOSSIP_SENDER_MAIN, 210);
				player->ADD_GOSSIP_ITEM(1, "Военачальник", GOSSIP_SENDER_MAIN, 211);
				player->ADD_GOSSIP_ITEM(1, "Оружие Ледомола", GOSSIP_SENDER_MAIN, 212);
				player->ADD_GOSSIP_ITEM(1, "Оберег", GOSSIP_SENDER_MAIN, 213);
				player->ADD_GOSSIP_ITEM(1, "+ 50 к выносливости", GOSSIP_SENDER_MAIN, 214);
				player->ADD_GOSSIP_ITEM(1, "+ 65 к силе атаки", GOSSIP_SENDER_MAIN, 215);
				player->ADD_GOSSIP_ITEM(1, "+ 63 к силе заклинаний", GOSSIP_SENDER_MAIN, 216);
				player->ADD_GOSSIP_ITEM(1, "Мангуст", GOSSIP_SENDER_MAIN, 217);
				player->ADD_GOSSIP_ITEM(1, "Палач", GOSSIP_SENDER_MAIN, 218);
				player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
				player->PlayerTalkClass->SendGossipMenu(100002, creature->GetGUID());
				return true;
			}
			else
			{
				player->GetSession()->SendNotification("У вас не одето леворучное оружие");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 14: //Remove enchant menu
			player->ADD_GOSSIP_ITEM(1, " Снять чары с правой руки", GOSSIP_SENDER_MAIN, 400);
			player->ADD_GOSSIP_ITEM(1, "Снять чары с левой руки", GOSSIP_SENDER_MAIN, 401);
			player->ADD_GOSSIP_ITEM(1, "Снять чары с двуручного оружия", GOSSIP_SENDER_MAIN, 413);
			player->ADD_GOSSIP_ITEM(1, "Снять чары с щита", GOSSIP_SENDER_MAIN, 412);
			player->ADD_GOSSIP_ITEM(1, "Снять чары с головы", GOSSIP_SENDER_MAIN, 402);
			player->ADD_GOSSIP_ITEM(1, "Снять чары с плеч", GOSSIP_SENDER_MAIN, 403);
			player->ADD_GOSSIP_ITEM(1, "Снять чары со спины", GOSSIP_SENDER_MAIN, 404);
			player->ADD_GOSSIP_ITEM(1, "Снять чары с груди", GOSSIP_SENDER_MAIN, 405);
			player->ADD_GOSSIP_ITEM(1, "Снять чары с запястьев", GOSSIP_SENDER_MAIN, 406);
			player->ADD_GOSSIP_ITEM(1, "Снять чары с рук", GOSSIP_SENDER_MAIN, 407);
			player->ADD_GOSSIP_ITEM(1, "Снять чары с ног", GOSSIP_SENDER_MAIN, 408);
			player->ADD_GOSSIP_ITEM(1, "Снять чары со ступней", GOSSIP_SENDER_MAIN, 409);
			if (player->HasSkill(SKILL_ENCHANTING) && player->GetSkillValue(SKILL_ENCHANTING) > 400)
			{
				player->ADD_GOSSIP_ITEM(1, "Снять чары с кольца # 1", GOSSIP_SENDER_MAIN, 410);
				player->ADD_GOSSIP_ITEM(1, "Снять чары с кольца # 2", GOSSIP_SENDER_MAIN, 411);
			}
			player->ADD_GOSSIP_ITEM(1, "Назад", GOSSIP_SENDER_MAIN, 300);
			player->PlayerTalkClass->SendGossipMenu(100014, creature->GetGUID());
			return true;
			break;

		case 100:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_AGILITY_1H);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 101:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_SPIRIT);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 102:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_BLADE_WARD);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 103:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_BLOOD_DRAINING);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 104:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_BERSERKING);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 105:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_ACCURACY);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 106:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_BLACK_MAGIC);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 107:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_BATTLEMASTER);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 108:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_ICEBREAKER);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 109:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_LIFEWARD);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 110:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_TITANGUARD);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 111:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_POTENCY);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 112:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_MIGHTY_SPELL_POWER);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 113:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_2WEP_MONGOOSE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 114:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_EXECUTIONER);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 115:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого нужно двуручное оружие");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_2WEP_GREATER_SPELL_POWER);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Вы не одели двуручное оружие");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 116:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого нужно двуручное оружие");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_2WEP_AGILITY);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Вы не одели двуручное оружие");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 117:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого нужно двуручное оружие");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_2WEP_MASSACRE);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Вы не одели двуручное оружие");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 118:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого нужен щит");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_DEFENSE);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Вы не одели щит");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 119:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого нужен щит");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_INTELLECT);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Вы не одели щит");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 120:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого нужен щит");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_RESILIENCE);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Вы не одели щит");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 121:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого нужен щит");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_TITANIUM_PLATING);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Вы не одели щит");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 122:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого нужен щит");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_STAMINA);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Вы не одели щит");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 123:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого нужен щит");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_TOUGHSHIELD);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Вы не одели щит");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 124:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_BLISSFUL_MENDING);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 125:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_BURNING_MYSTERIES);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 126:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_DOMINANCE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 127:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_SAVAGE_GLADIATOR);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 128:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_STALWART_PROTECTOR);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 129:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_TORMENT);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 130:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_TRIUMPH);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 131:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_ECLIPSED_MOON);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 132:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_FLAME_SOUL);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 133:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_FLEEING_SHADOW);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 134:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_FROSTY_SOUL);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 135:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_TOXIC_WARDING);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 136:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_MASTERS_AXE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 137:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_MASTERS_CRAG);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 138:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_MASTERS_PINNACLE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 139:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_MASTERS_STORM);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 140:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_GREATER_AXE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 141:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_GREATER_CRAG);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 142:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_GREATER_GLADIATOR);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 143:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_GREATER_PINNACLE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 144:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_GREATER_STORM);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 145:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_DOMINANCE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 146:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_TRIUMPH);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 147:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_SPRINGY_ARACHNOWEAVE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 148:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_SHADOW_ARMOR);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 149:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_DARKGLOW_EMBROIDERY);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 150:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_LIGHTWEAVE_EMBROIDERY);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 151:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_SWORDGUARD_EMBROIDERY);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 152:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_WISDOM);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 153:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_TITANWEAVE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 154:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_SPELL_PIERCING);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 155:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_MIGHTY_ARMOR);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 156:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_MAJOR_AGILITY);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 157:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_GREATER_SPEED);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 158:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_POWERFUL_STATS);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 159:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_SUPER_HEALTH);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 160:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_GREATER_MAINA_REST);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 161:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_EXCEPTIONAL_RESIL);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 162:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_GREATER_DEFENSE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 163:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_MAJOR_STAMINA);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 164:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_SUPERIOR_SP);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 165:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_GREATER_ASSUALT);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 166:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_MAJOR_SPIRT);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 167:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_EXPERTISE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 168:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_GREATER_STATS);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 169:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_INTELLECT);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 170:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_ARCANE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 171:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_FIRE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 172:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_FROST);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 173:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_NATURE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 174:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_SHADOW);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 175:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_ATTACK);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 176:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_STAMINA);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 177:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_SPELLPOWER);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 178:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_GREATER_BLASTING);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 179:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_ARMSMAN);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 180:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_CRUSHER);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 181:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_AGILITY);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 182:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_PRECISION);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 183:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_EXPERTISE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 184:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_EARTHEN);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 185:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_FROSTHIDE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 186:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_ICESCALE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 187:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_BRILLIANT_SPELLTHREAD);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 188:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_SAPPHIRE_SPELLTHREAD);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 189:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_DRAGONSCALE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 190:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_WYRMSCALE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 191:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_GREATER_ASSULT);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 192:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_TUSKARS_VITLIATY);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 193:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_SUPERIOR_AGILITY);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 194:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_GREATER_SPIRIT);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 195:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_GREATER_VITALITY);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 196:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_ICEWALKER);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 197:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_GREATER_FORTITUDE);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 198:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_NITRO_BOOTS);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 199:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_BOOTS_PYRO_ROCKET);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 200:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_HYPERSPEED);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 201:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_ARMOR_WEBBING);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 202:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), ENCHANT_RING_ASSULT);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 203:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), ENCHANT_RING_GREATER_SP);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 204:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), ENCHANT_RING_STAMINA);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 2022:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), ENCHANT_RING_ASSULT);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 2032:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), ENCHANT_RING_GREATER_SP);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 2042:
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), ENCHANT_RING_STAMINA);
			player->CLOSE_GOSSIP_MENU();
			break;

		case 205:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_BLADE_WARD);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 206:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_AGILITY_1H);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 207:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_SPIRIT);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 208:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_BERSERKING);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 209:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_ACCURACY);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 210:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_BLACK_MAGIC);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 211:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_BATTLEMASTER);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 212:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_ICEBREAKER);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 213:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_LIFEWARD);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 214:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_TITANGUARD);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 215:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_POTENCY);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 216:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_MIGHTY_SPELL_POWER);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 217:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_2WEP_MONGOOSE);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 218:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_EXECUTIONER);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 219:
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_BLOOD_DRAINING);
				player->CLOSE_GOSSIP_MENU();
			}
			else
			{
				player->GetSession()->SendAreaTriggerMessage("Для этого должно быть одето оружие левой руки");
				player->CLOSE_GOSSIP_MENU();
			}
		}
		break;

		case 300: //Назад menu
		{
			player->ADD_GOSSIP_ITEM(1, "Зачарить Правую руку", GOSSIP_SENDER_MAIN, 1);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Левую руку", GOSSIP_SENDER_MAIN, 13);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Двуручное Оружие", GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Щит", GOSSIP_SENDER_MAIN, 3);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Голову", GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Плечи", GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Спину", GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Грудь", GOSSIP_SENDER_MAIN, 7);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Запястья", GOSSIP_SENDER_MAIN, 8);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Руки", GOSSIP_SENDER_MAIN, 9);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Ноги", GOSSIP_SENDER_MAIN, 10);
			player->ADD_GOSSIP_ITEM(1, "Зачарить Ступни", GOSSIP_SENDER_MAIN, 11);

			if (player->HasSkill(SKILL_ENCHANTING) && player->GetSkillValue(SKILL_ENCHANTING) > 400)
			{
				player->ADD_GOSSIP_ITEM(1, "Зачарить Кольцо # 1", GOSSIP_SENDER_MAIN, 12);
				player->ADD_GOSSIP_ITEM(1, "Зачарить Кольцо # 2", GOSSIP_SENDER_MAIN, 1200);
			}
			player->ADD_GOSSIP_ITEM(1, "Я хотел бы снять мои чары", GOSSIP_SENDER_MAIN, 14);
			player->PlayerTalkClass->SendGossipMenu(100001, creature->GetGUID());
			return true;
		}
		break;

		case 400: //Remove enchant for mainhand
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 401: //Remove enchant for offhand
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 402: //Remove enchant for head
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 403: //Remove enchant for shoulders
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 404: //remove enchant for cloak
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 405: //remove enchant for chest
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 406: //remove enchant for bracers
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 407: //remove enchant for gloves
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 408: //remove enchant for legs
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 409: //remove enchant for feet
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 410:
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 411:
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 412: // Снять чары со щита
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND));
			player->CLOSE_GOSSIP_MENU();
			break;

		case 413: // Снять чары с двуручного оружия
			RemoveEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND));
			player->CLOSE_GOSSIP_MENU();
			break;
		}
		return true;
	}
};

class Unell_Vendor_Reg_VIP : public CreatureScript
{
  public:
	Unell_Vendor_Reg_VIP() : CreatureScript("Unell_Vendor_Reg_VIP") {}

	bool OnGossipHello(Player *player, Creature *creature)
	{
		ChatHandler handler(player->GetSession());

		if (!player->GetSession()->IsPremium())
		{
			player->CLOSE_GOSSIP_MENU();
			creature->MonsterWhisper("Если ты считаешь себя за VIP, то что-то пошло не так...", player, false);
			return true;
		}

		/*if (player->IsGameMaster())
		{
			creature->Whisper("Решил зайти из под ГМ, ну окей, тут я уже ничего не сделаю....", LANG_UNIVERSAL, player, false);
			return true;
		}*/

		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\inv_misc_gem_01:25|t Ювелирное дело", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\trade_mining:25|t Горное дело", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\trade_tailoring.:25|t Портяжное дело", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\inv_inscription_tradeskill01:25|t Начертание", GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\trade_engineering:25|t Инженерное дело", GOSSIP_SENDER_MAIN, 5);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\trade_engraving:25|t Наложение чар", GOSSIP_SENDER_MAIN, 6);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\inv_misc_armorkit_17:25|t Кожевничество", GOSSIP_SENDER_MAIN, 7);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\trade_alchemy:25|t Алхимия", GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\inv_elemental_eternal_shadow:25|t Разные товары", GOSSIP_SENDER_MAIN, 9);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\inv_misc_herb_icethorn:25|t Мяско Рыбка Травка", GOSSIP_SENDER_MAIN, 10);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\inv_hammer_20:25|t Устройства | Приспособления", GOSSIP_SENDER_MAIN, 11);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 uiSender, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{
		case 1: // Юва
			player->GetSession()->SendListInventory(creature->GetGUID(), 560000);
			break;
		case 2: //
			player->GetSession()->SendListInventory(creature->GetGUID(), 551000);
			break;
		case 3: //
			player->GetSession()->SendListInventory(creature->GetGUID(), 558000);
			break;
		case 4: //
			player->GetSession()->SendListInventory(creature->GetGUID(), 557000);
			break;
		case 5: //
			player->GetSession()->SendListInventory(creature->GetGUID(), 555000);
			break;
		case 6: //
			player->GetSession()->SendListInventory(creature->GetGUID(), 556000);
			break;
		case 7: //
			player->GetSession()->SendListInventory(creature->GetGUID(), 552000);
			break;
		case 8: //
			player->GetSession()->SendListInventory(creature->GetGUID(), 550000);
			break;
		case 9: //
			player->GetSession()->SendListInventory(creature->GetGUID(), 553000);
			break;
		case 10: //
			player->GetSession()->SendListInventory(creature->GetGUID(), 559000);
			break;
		case 11: //
			player->GetSession()->SendListInventory(creature->GetGUID(), 554000);
			break;
		}
		return true;
	}
};

class gamble_npc : public CreatureScript
{
  public:
	gamble_npc() : CreatureScript("gamble_npc") {}

	// How much $$$ the player has
	uint32 Pocket = 0;

	// Bets
	uint32 Bets = 0; // # of bets placed
	uint32 Wins = 0; // # of wins

	bool OnGossipHello(Player *player, Creature *creature)
	{
		// Get bet amounts from config
		uint32 Bet1 = sConfigMgr->GetIntDefault("Gambler.Amount1", 1);
		uint32 Bet2 = sConfigMgr->GetIntDefault("Gambler.Amount2", 2);
		uint32 Bet3 = sConfigMgr->GetIntDefault("Gambler.Amount3", 3);
		uint32 Bet4 = sConfigMgr->GetIntDefault("Gambler.Amount4", 4);
		uint32 Bet5 = sConfigMgr->GetIntDefault("Gambler.Amount5", 5);
		uint32 Jackpot = sConfigMgr->GetIntDefault("Gambler.Jackpot", 50);

		player->PlayerTalkClass->ClearMenus();

		Bets = 0;					 // Reset # of bets placed
		Pocket = player->GetMoney(); // How much gold does the player have?

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "Раз два", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Разработка] Раз два три", GOSSIP_SENDER_MAIN, 7);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "[Разработка] Изучить правила", GOSSIP_SENDER_MAIN, 7);
		player->SEND_GOSSIP_MENU(601020, creature->GetGUID());
		return true;
	}

	// Gossip Select
	bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();

		// Get bet amounts from config
		uint32 Bet1 = sConfigMgr->GetIntDefault("Gambler.Amount1", 1);
		uint32 Bet2 = sConfigMgr->GetIntDefault("Gambler.Amount2", 2);
		uint32 Bet3 = sConfigMgr->GetIntDefault("Gambler.Amount3", 3);
		uint32 Bet4 = sConfigMgr->GetIntDefault("Gambler.Amount4", 4);
		uint32 Bet5 = sConfigMgr->GetIntDefault("Gambler.Amount5", 5);
		uint32 Jackpot = sConfigMgr->GetIntDefault("Gambler.Jackpot", 50);

		std::ostringstream Option1;
		std::ostringstream Option2;
		std::ostringstream Option3;
		std::ostringstream Option4;
		std::ostringstream Option5;
		std::ostringstream messageInstruct;

		if (sender != GOSSIP_SENDER_MAIN)
			return false;

		switch (uiAction)
		{

		case 1:
			Option1 << "Поставить " << Bet1 << " золота";
			Option2 << "Поставить " << Bet2 << " золота";
			Option3 << "Поставить " << Bet3 << " золота";
			Option4 << "Поставить " << Bet4 << " золота";
			Option5 << "Поставить " << Bet5 << " золота";
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, Option1.str(), GOSSIP_SENDER_MAIN, 2);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, Option2.str(), GOSSIP_SENDER_MAIN, 3);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, Option3.str(), GOSSIP_SENDER_MAIN, 4);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, Option4.str(), GOSSIP_SENDER_MAIN, 5);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, Option5.str(), GOSSIP_SENDER_MAIN, 6);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Назад", GOSSIP_SENDER_MAIN, 7);
			player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
			break;

		case 2:
			OnGossipSelectGold(player, creature, 1, 1, Bet1);
			break;

		case 3:
			OnGossipSelectGold(player, creature, 1, 1, Bet2);
			break;

		case 4:
			OnGossipSelectGold(player, creature, 1, 1, Bet3);
			break;

		case 5:
			OnGossipSelectGold(player, creature, 1, 1, Bet4);
			break;

		case 6:
			OnGossipSelectGold(player, creature, 1, 1, Bet5);
			break;

		case 7:
			player->PlayerTalkClass->ClearMenus();
			OnGossipHello(player, creature);
			break;
		}

		return true;
	}

	// Gossip Select Gold
	bool OnGossipSelectGold(Player *player, Creature *creature, uint32 sender, uint32 uiAction, uint32 gold)
	{
		player->PlayerTalkClass->ClearMenus();

		// Get bet amounts from config
		uint32 Bet1 = sConfigMgr->GetIntDefault("Gambler.Amount1", 1);
		uint32 Bet2 = sConfigMgr->GetIntDefault("Gambler.Amount2", 2);
		uint32 Bet3 = sConfigMgr->GetIntDefault("Gambler.Amount3", 3);
		uint32 Bet4 = sConfigMgr->GetIntDefault("Gambler.Amount4", 4);
		uint32 Bet5 = sConfigMgr->GetIntDefault("Gambler.Amount5", 5);
		uint32 Jackpot = sConfigMgr->GetIntDefault("Gambler.Jackpot", 50);

		uint32 Roll = 0;   // Dice roll
		uint32 Amount = 0; // Bet amount

		Roll = urand(1, 1000);
		Amount = gold * 10000; // Convert copper to gold
		player->ModifyMoney(-Amount);

		if (Roll == 1000)
		{
			std::ostringstream messageAction;
			std::ostringstream messageNotice;

			player->ModifyMoney(Jackpot * 10000);
			player->PlayDirectSound(3337);
			player->CastSpell(player, 47292);
			player->CastSpell(player, 44940);

			messageAction << "Кости остановились с общим броском " << Roll << ".";
			//messageNotice << "Вы выйграли джекпот! Сумма выйгрыша составляет " << Jackpot << " золота!";
			creature->MonsterWhisper(messageAction.str().c_str(), player);
			player->GetSession()->SendNotification("Вы выйграли джекпот! Сумма выйгрыша составляет %u золота!", Jackpot);
			player->CLOSE_GOSSIP_MENU();
			creature->HandleEmoteCommand(EMOTE_ONESHOT_APPLAUD);
			return true;
		}
		else if (Roll >= 500)
		{
			std::ostringstream messageAction;
			std::ostringstream messageNotice;

			player->ModifyMoney(Amount * 2);
			player->PlayDirectSound(3337);
			player->CastSpell(player, 47292);
			player->CastSpell(player, 44940);
			messageAction << "Кости остановились с общим броском " << Roll << ".";
			//messageNotice << "Поздравляю, Вы удвоили поставленные средства. Ваш выигрыш " << Amount / 10000 * 2 << " золота!";
			creature->MonsterWhisper(messageAction.str().c_str(), player);
			player->GetSession()->SendNotification("Поздравляю, Вы удвоили поставленные средства. Ваш выигрыш %u золота!", Amount / 10000 * 2);
			creature->HandleEmoteCommand(EMOTE_ONESHOT_APPLAUD);
		}
		else
		{
			std::ostringstream messageAction;
			std::ostringstream messageNotice;
			messageAction << "Кости остановились с общим броском " << Roll << ".";
			messageNotice << "Мне жаль, но Вы проиграли " << Amount / 10000 << " золота!";
			creature->MonsterWhisper(messageAction.str().c_str(), player);
			player->GetSession()->SendNotification("Мне жаль, но Вы проиграли %u золота", Amount / 10000);
			creature->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
		}

		OnGossipSelect(player, creature, GOSSIP_SENDER_MAIN, 1);
		return true;
	}

	struct gambler_passivesAI : public ScriptedAI
	{
		gambler_passivesAI(Creature *creature) : ScriptedAI(creature) {}

		uint32 uiAdATimer;
		uint32 uiAdCTimer;

		void Reset()
		{
			uiAdATimer = 1000;
			uiAdCTimer = 30000;
		}

		void UpdateAI(uint32 diff)
		{

			if (uiAdATimer <= diff)
			{
				me->MonsterSay("Приходите, приходите все! Делайте свои ставки, делайте ставки!", LANG_UNIVERSAL, NULL);
				me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
				me->CastSpell(me, 44940);
				uiAdATimer = 61000;
			}
			else
				uiAdATimer -= diff;

			if (uiAdCTimer <= diff)
			{
				me->MonsterSay("Не заставляйте меня грустить, Приходи и играй! Шаг вперед и победа твоя!", LANG_UNIVERSAL, NULL);
				me->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
				uiAdCTimer = 61000;
			}
			else
				uiAdCTimer -= diff;
		}
	};

	CreatureAI *GetAI(Creature *creature) const
	{
		return new gambler_passivesAI(creature);
	}
};

class Professions_NPC : public CreatureScript
{
public:
	Professions_NPC() : CreatureScript("Professions_NPC") {}

	void CreatureWhisperBasedOnBool(const char *text, Creature *_creature, Player *pPlayer, bool value)
	{
		if (value)
			_creature->MonsterTextEmote(text, pPlayer);
	}

	uint32 PlayerMaxLevel() const
	{
		return sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
	}

	bool PlayerHasItemOrSpell(const Player *plr, uint32 itemId, uint32 spellId) const
	{
		return plr->HasItemCount(itemId, 1, true) || plr->HasSpell(spellId);
	}

	bool OnGossipHello(Player *pPlayer, Creature* _creature)
	{
		if (sConfigMgr->GetBoolDefault("Unell.NPC.Professions.OnlyVIP", true) && !pPlayer->GetSession()->IsPremium())
		{
			_creature->MonsterWhisper("Я могу помочь только VIP игрокам...", pPlayer, false);
			pPlayer->CLOSE_GOSSIP_MENU();
			return false;
		}

		pPlayer->ADD_GOSSIP_ITEM(9, "[Профессии] ->", GOSSIP_SENDER_MAIN, 196);
		pPlayer->PlayerTalkClass->SendGossipMenu(907, _creature->GetGUID());
		return true;
	}

	bool PlayerAlreadyHasTwoProfessions(const Player *pPlayer) const
	{
		uint32 skillCount = 0;

		if (pPlayer->HasSkill(SKILL_MINING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_SKINNING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_HERBALISM))
			skillCount++;

		if (skillCount >= 2)
			return true;

		for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
		{
			SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
			if (!SkillInfo)
				continue;

			if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
				continue;

			if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
				continue;

			const uint32 skillID = SkillInfo->id;
			if (pPlayer->HasSkill(skillID))
				skillCount++;

			if (skillCount >= 2)
				return true;
		}
		return false;
	}

	bool LearnAllRecipesInProfession(Player *pPlayer, SkillType skill)
	{
		ChatHandler handler(pPlayer->GetSession());
		char* skill_name;

		SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
		skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];

		LearnSkillRecipesHelper(pPlayer, SkillInfo->id);

		pPlayer->SetSkill(SkillInfo->id, pPlayer->GetSkillStep(SkillInfo->id), 450, 450);
		handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);

		return true;
	}

	void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
	{
		uint32 classmask = player->getClassMask();

		for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
		{
			SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
			if (!skillLine)
				continue;

			// wrong skill
			if (skillLine->skillId != skill_id)
				continue;

			// not high rank
			if (skillLine->forward_spellid)
				continue;

			// skip racial skills
			if (skillLine->racemask != 0)
				continue;

			// skip wrong class skills
			if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
				continue;

			SpellInfo const * spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
			if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo))
				continue;

			player->learnSpell(skillLine->spellId);
		}
	}

	bool IsSecondarySkill(SkillType skill) const
	{
		return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
	}

	void CompleteLearnProfession(Player *pPlayer, Creature *pCreature, SkillType skill)
	{
		if (PlayerAlreadyHasTwoProfessions(pPlayer) && !IsSecondarySkill(skill))
			pCreature->MonsterTextEmote("Вы уже изучили 2 профессии!", pPlayer);
		else
		{
			if (!LearnAllRecipesInProfession(pPlayer, skill))
				pCreature->MonsterTextEmote("Internal error occured!", pPlayer);
		}
	}

	bool OnGossipSelect(Player* pPlayer, Creature* _creature, uint32 uiSender, uint32 uiAction)
	{
		pPlayer->PlayerTalkClass->ClearMenus();

		if (uiSender == GOSSIP_SENDER_MAIN)
		{

			switch (uiAction)
			{
			case 196:
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_alchemy:30|t Алхимия.", GOSSIP_SENDER_MAIN, 1);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Ingot_05:30|t Кузнечное дело.", GOSSIP_SENDER_MAIN, 2);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Misc_LeatherScrap_02:30|t Кожевничество.", GOSSIP_SENDER_MAIN, 3);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Fabric_Felcloth_Ebon:30|t Портняжное дело.", GOSSIP_SENDER_MAIN, 4);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_wrench_01:30|t Инженерное дело.", GOSSIP_SENDER_MAIN, 5);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_engraving:30|t Наложение чар.", GOSSIP_SENDER_MAIN, 6);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_gem_01:30|t Ювелирное дело.", GOSSIP_SENDER_MAIN, 7);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Scroll_08:30|t Начертание.", GOSSIP_SENDER_MAIN, 8);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Misc_Herb_07:30|t Травничество.", GOSSIP_SENDER_MAIN, 9);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_pelt_wolf_01:30|t Снятие шкур.", GOSSIP_SENDER_MAIN, 10);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_mining:30|t Горное дело.", GOSSIP_SENDER_MAIN, 11);
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_fishing:30|t Рыболовное дело.", GOSSIP_SENDER_MAIN, 13);
				pPlayer->PlayerTalkClass->SendGossipMenu(1, _creature->GetGUID());
				break;
			case 1:
				if (pPlayer->HasSkill(SKILL_ALCHEMY))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_ALCHEMY);

				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 2:
				if (pPlayer->HasSkill(SKILL_BLACKSMITHING))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_BLACKSMITHING);

				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 3:
				if (pPlayer->HasSkill(SKILL_LEATHERWORKING))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_LEATHERWORKING);

				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 4:
				if (pPlayer->HasSkill(SKILL_TAILORING))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_TAILORING);

				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 5:
				if (pPlayer->HasSkill(SKILL_ENGINEERING))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_ENGINEERING);

				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 6:
				if (pPlayer->HasSkill(SKILL_ENCHANTING))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_ENCHANTING);

				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 7:
				if (pPlayer->HasSkill(SKILL_JEWELCRAFTING))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_JEWELCRAFTING);

				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 8:
				if (pPlayer->HasSkill(SKILL_INSCRIPTION))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_INSCRIPTION);

				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 9:
				if (pPlayer->HasSkill(SKILL_HERBALISM))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_HERBALISM);
				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 10:
				if (pPlayer->HasSkill(SKILL_SKINNING))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_SKINNING);
				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 11:
				if (pPlayer->HasSkill(SKILL_MINING))
				{
					pPlayer->PlayerTalkClass->SendCloseGossip();
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_MINING);
				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			case 12:
				pPlayer->PlayerTalkClass->SendCloseGossip();
				break;
			}
		}
		return true;
	}
};

void AddSC_Unell_Custom_NPC()
{
	new ralph();
	new npc_welcome();
	new Professions_NPC();
	new Unell_Lottery();
	new Unell_Prize_OBT();
	new npc_enchantment_private();
	new Unell_Vendor_Reg_VIP();
	new gamble_npc();
	new Unell_Prize_NewYear();
	new Professions_NPC_Test();
}