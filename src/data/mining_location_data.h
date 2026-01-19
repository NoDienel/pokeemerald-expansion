#ifndef GUARD_MINING_LOCATION_DATA_H
#define GUARD_MINING_LOCATION_DATA_H

#include "constants/mining_minigame.h"

struct LocSysFossilData
{
    u32 chance;
    u32 fossilItemId;
};

struct LocSysLocationData
{
    const struct LocSysFossilData *fossils;
    u32 count;
};

// Global array mapping Location IDs to their fossil data
// Only ITEM_POKEFOSSIL_001 through ITEM_POKEFOSSIL_131 are mapped to their Pokémon species
// POKEFOSSILS 132+ (legendaries, mythicals, etc) are excluded from mining distribution
static const struct LocSysLocationData LocationData[] =
{
    // Test Location
    [LOCATIONID_TEST_1] = 
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 33, .fossilItemId = ITEM_POKEFOSSIL_001 },  // Wood Gecko (Treecko)
            { .chance = 33, .fossilItemId = ITEM_POKEFOSSIL_002 },  // Fire Cat (Litten)
            { .chance = 34, .fossilItemId = ITEM_POKEFOSSIL_003 },  // Big Jaw (Totodile)
        },
        .count = 3
    },
    
    // TOWNS - Generally rare fossil locations with common items
    [LOCATIONID_PETALBURGCITY_0] = // Starter area
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_006 },  // Firefly (Male) (Volbeat)
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_007 },  // Firefly (Female) (Illumise)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_008 },  // Mantis (Scyther)
        },
        .count = 3
    },

    [LOCATIONID_PETALBURGCITY_1] = // Bottom of lake
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_091 },  // Heart (Luvdisk)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_095 },  // River Crab (Krabby)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_092 },  // Common Fish (Basculin)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_100 },  // Nigiri Sushi (Tatsugiri)
        },
        .count = 4
    },
    
    [LOCATIONID_SLATEPORTCITY_0] = // Coastal Town
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_009 },  // String Ball (Tarountula)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_010 },  // Grasshopper (Nymble)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_011 },  // Bagworm (Burmy)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_012 },  // Tiny Bee (Combee)
        },
        .count = 4
    },
    
    [LOCATIONID_MAUVILLECITY_0] = // Town ontop of generator
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_013 },  // Larva (Blipbug)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_014 },  // Attached (Joltik)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_072 },  // Lightning (Electrike)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_073 },  // Thunderbolt (Blitzle)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_121 },  // Virtual (Porygon)
        },
        .count = 5
    },
    
    [LOCATIONID_RUSTBOROCITY_0] = //Ghost town
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_085 },  // Skull (Duskull)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_082 },  // Puppet (Shuppet)
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_086 },  // Vocal Cord (Misdreavus)
            { .chance = 3, .fossilItemId = ITEM_POKEFOSSIL_047 },  // Matcha (Poltchageist)
            { .chance = 2, .fossilItemId = ITEM_POKEFOSSIL_065 },  // Paleozoic (Genesect)
        },
        .count = 5
    },
    
    [LOCATIONID_FORTREECITY_0] = //Treetop city
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_020 },  // Scout Tail (Sentret)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_021 },  // Lookout Rat (Patrat)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_022 },  // Loiter Weasel (Yugoos)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_023 },  // Scratch Cat (Meowth)
        },
        .count = 4
    },
    
    [LOCATIONID_LILYCOVECITY_0] = //Urbanized City
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_024 },  // Coupled (Tandemaus)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_025 },  // Whispering (Whismur)
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_032 },  // Stomach (Gulpin)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_027 },  // Cat Ferret (Zangoose)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_114 },  // Sand Heap (Sandygast)
        },
        .count = 5
    },

    [LOCATIONID_LILYCOVECITY_1] = //Beach area
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_114 },  // Sand Heap (Sandygast)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_096 },  // Barnacle (Binacle)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_112 },  // Mud Trap (Stunfisk)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_075 },  // Tiny Metal Bird (Rookidee)
        },
        .count = 4
    },
    
    [LOCATIONID_MOSSDEEPCITY_0] = //Island
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_092 },  // Common Fish (Basculin)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_093 },  // Bullet Jet (Remoraid)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_030 },  // Sea Lily (Lileep)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_055 },  // Spiral (Omanyte)
        },
        .count = 4
    },
    
    [LOCATIONID_SOOTOPOLISCITY_0] = //Hidden City
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_032 },  // Stomach (Gulpin)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_033 },  // Toxic Lizard (Salandit)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_034 },  // Scorpion (Skorupi)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_035 },  // Toxic Mouth (Croagunk)
        },
        .count = 4
    },
    
    [LOCATIONID_EVERGRANDECITY_0] = //Endgame
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_036 },  // Pig Monkey (Mankey)
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_037 },  // Thrusting Arm (Makuhita)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_038 },  // Lone Warrior (Falink)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_039 },  // Emanating (Riolu)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_040 },  // Smirking Panda (Pancham)
        },
        .count = 5
    },
    
    [LOCATIONID_LITTLEROOTTOWN_0] = //Starting Town
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 50, .fossilItemId = ITEM_POKEFOSSIL_041 },  // Mushroom (Shroomish)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_042 },  // Seed (Sunkern)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_043 },  // Cottonweed (Hoppip)
        },
        .count = 3
    },
    
    [LOCATIONID_OLDDALETOWN_0] = //Town that was split down the middle by the formation of a river
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 45, .fossilItemId = ITEM_POKEFOSSIL_044 },  // Rubber Fruit (Bounsweet)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_045 },  // Glowing Spore (Morelull)
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_046 },  // Spicy Pepper (Capsakid)
        },
        .count = 3
    },
    
    [LOCATIONID_DEWFORDTOWN_0] = //Beach Town
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_047 },  // Matcha (Poltchageist)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_048 },  // Olive (Smoliv)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_049 },  // Cactus (Cacnea)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_050 },  // Acorn (Seedot)
        },
        .count = 4
    },
    
    [LOCATIONID_LAVARIDGETOWN_0] = //Old folks town with natural hot springs and sandy spa
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 100, .fossilItemId = ITEM_POKEFOSSIL_051 },  // Disasterous (Absol)
        },
        .count = 1
    },
    
    [LOCATIONID_FALLARBORTOWN_0] = //Ashy town with meteor activity, near meteor falls
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 100, .fossilItemId = ITEM_POKEFOSSIL_052 },  // Strong Bite (Poochyena)
        },
        .count = 1
    },
    
    [LOCATIONID_VERDANTURFTOWN_0] = //Flowery town in a field
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 100, .fossilItemId = ITEM_POKEFOSSIL_053 },  // Bonsai (Bonsly)
        },
        .count = 1
    },
    
    [LOCATIONID_PACIFIDLOGTOWN_0] = //Floating town
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_054 },  // Shellfish (Kabuto)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_055 },  // Spiral (Omanyte)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_056 },  // Amber (Aerodactyl)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_057 },  // Sea Lily (Lileep)
        },
        .count = 4
    },
    
    // ROUTES - More abundant fossil locations
    // Routes 101-103: Early routes with starter complements and common types
    [LOCATIONID_ROUTE_101_0] = //Starter route 1
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_019 },  // Tiny Raccoon (Zigzagoon)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_024 },  // Coupled (Tandemaus)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_025 },  // Whispering (Whismur)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_026 },  // Spot Panda (Spinda)
        },
        .count = 4
    },
    
    [LOCATIONID_ROUTE_102_0] = //Starter route 2
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_004 },  // Ladybug (Ledyba)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_005 },  // Bee Fly (Cutiefly)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_006 },  // Firefly (Male) (Volbeat)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_007 },  // Firefly (Female) (Illumise)
        },
        .count = 4
    },
    
    [LOCATIONID_ROUTE_103_0] = //Starter route with a secret river crossing connection to route 110
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_008 },  // Mantis (Scyther)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_017 },  // Hairy Bug (Weedle)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_018 },  // Wild Duck (Farfetchd)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_027 },  // Cat Ferret (Zangoose)
        },
        .count = 4
    },
    
    // Routes 104-110: Water/Coastal routes (marine/aquatic fossils)
    [LOCATIONID_ROUTE_104_0] = //Coastal route that containst the southern entrance to petalburg woods
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_054 },  // Shellfish (Kabuto)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_055 },  // Spiral (Omanyte)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_057 },  // Sea Lily (Lileep)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_058 },  // Old Shrimp (Anorith)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_056 },  // Amber (Aerodactyl)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_105_0] = //First ocean route
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_092 },  // Common Fish (Basculin)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_093 },  // Bullet Jet (Remoraid)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_094 },  // Octopus (Clobbopus)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_095 },  // River Crab (Krabby)
        },
        .count = 4
    },
    
    [LOCATIONID_ROUTE_106_0] = //North of dewford, has a lot of rocky outcroppings
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_092 },  // Common Fish (Basculin)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_096 },  // Barnacle (Binacle)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_097 },  // Sea Slug (Shellos)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_091 },  // Heart (Luvdisk)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_107_0] = //Water but also is near Dewford
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_092 },  // Common Fish (Basculin)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_099 },  // Big Catfish (Dondozo)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_101 },  // Kelp (Skrelp)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_061 },  // Prototurtle (Tirtouga)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_100 },  // Nigiri Sushi (Tatsugiri)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_108_0] = //Completely water
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 60, .fossilItemId = ITEM_POKEFOSSIL_092 },  // Common Fish (Basculin)
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_093 },  // Bullet Jet (Remoraid)
        },
        .count = 2
    },
    
    [LOCATIONID_ROUTE_109_0] = //South of Slateport, has a sandbar
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_092 },  // Common Fish (Basculin)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_114 },  // Sand Heap (Sandygast)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_096 },  // Barnacle (Binacle)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_112 },  // Mud Trap (Stunfisk)
        },
        .count = 4
    },
    
    [LOCATIONID_ROUTE_110_0] =  //south of mauville (plustle minun)
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_028 },  // Fang Snake (Seviper)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_027 },  // Cat Ferret (Zangoose)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_030 },  // Poison Pin (Female) (Nidoran F)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_031 },  // Poison Pin (Male) (Nidoran M)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_069 },  // Cheering + (Plusle)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_070 },  // Cheering - (Minun)
        },
        .count = 6
    },
    
    // Routes 111-113: Desert/Volcanic routes
    [LOCATIONID_ROUTE_111_0] = // Desert Route
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_115 },  // Desert Croc (Sandile)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_112 },  // Mud Trap (Stunfisk)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_113 },  // Rolling (Rellor)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_114 },  // Sand Heap (Sandygast)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_050 },  // Acorn (Seedot)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_112_0] = //Part desert, part mountain
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_117 },  // Magma Geode (Numel)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_118 },  // Lava (Slugma)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_119 },  // Candle (Litwick)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_120 },  // Fire Child (Charcadet)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_103 },  // Anteater (Heatmor)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_113_0] = //Ashy route north of the desert, famous home of spinda, west of Fallarbor
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_049 },  // Cactus (Cacnea)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_042 },  // Seed (Sunkern)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_043 },  // Cottonweed (Hoppip)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_044 },  // Rubber Fruit (Bounsweet)
        },
        .count = 4
    },
    
    [LOCATIONID_ROUTE_114_0] = //East of fallarbor, transitions ashy route to mountain through a lake
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_059 },  // Hard Head (Cranidos)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_060 },  // Shield (Shieldon)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_064 },  // Ice Sail (Amaura)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_063 },  // Royal Dino (Tyrunt)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_051 },  // Disasterous (Absol)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_115_0] = //North of rustburrow city
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_127 },  // Ice Chunk (Bergmite)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_128 },  // Ice Fin (Frigibax)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_129 },  // Bat Ear (Noibat)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_130 },  // Tusk (Axew)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_131 },  // Scaly (Jangmo-o)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_116_0] = //Connects rustburrow to verdanturf, road is carved through a mountain
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_123 },  // Snow Hat (Snorunt)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_124 },  // Cold Pig (Swinub)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_125 },  // Sharp Claw (Sneasel)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_126 },  // Tundra Whale (Cetoddle)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_111 },  // Fly Scorpion (Gligar)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_117_0] = //Grassy plains
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_009 },  // String Ball (Tarountula)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_010 },  // Grasshopper (Nymble)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_011 },  // Bagworm (Burmy)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_012 },  // Tiny Bee (Combee)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_013 },  // Larva (Blipbug)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_118_0] = //Beach area with some grass
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_015 },  // Bug Shroom (Paras)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_016 },  // Radiator (Sizzlipede)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_047 },  // Matcha (Poltchageist)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_084 },  // Stump (Phantump)
        },
        .count = 4
    },
    
    [LOCATIONID_ROUTE_119_0] = //Jungle area
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 34, .fossilItemId = ITEM_POKEFOSSIL_041 },  // Mushroom (Shroomish)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_045 },  // Glowing Spore (Morelull)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_046 },  // Spicy Pepper (Capsakid)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_048 },  // Olive (Smoliv)
            { .chance = 1, .fossilItemId = ITEM_POKEFOSSIL_098 },  // Ugly Fish (Feebas)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_120_0] = //Jungle adjacent, winds over a river
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_021 },  // Lookout Rat (Patrat)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_022 },  // Loiter Weasel (Yugoos)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_023 },  // Scratch Cat (Meowth)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_062 },  // First Bird (Archen)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_053 },  // Bonsai (Bonsly)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_121_0] = // Route to the left of Lilicove, industrialized and toxic
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_032 },  // Stomach (Gulpin)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_034 },  // Scorpion (Skorupi)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_033 },  // Toxic Lizard (Salandit)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_035 },  // Toxic Mouth (Croagunk)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_071 },  // Toxic Baby (Toxel)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_122_0] = //Basically just the water around the ghostly Mt Pyre
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_075 },  // Tiny Metal Bird (Rookidee)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_076 },  // Gear (Klink)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_077 },  // Key Ring (Klefki)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_078 },  // Deceptive (Mawile)
        },
        .count = 4
    },
    
    [LOCATIONID_ROUTE_123_0] = //Connecing route between 118 and 112, contains a berry farm
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_009 },  // String Ball (Tarountula)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_010 },  // Grasshopper (Nymble)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_011 },  // Bagworm (Burmy)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_012 },  // Tiny Bee (Combee)
        },
        .count = 4
    },
    
    //124-134 More ocean routes
    [LOCATIONID_ROUTE_124_0] = //Right of Lilycove, polluted waters
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_085 },  // Skull (Duskull)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_086 },  // Vocal Cord (Misdreavus)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_087 },  // Tiny Birdbrain (Natu)
        },
        .count = 4
    },
    
    [LOCATIONID_ROUTE_125_0] = //North of Mossdeep, cold waters
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_088 },  // Bell (Chingling)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_089 },  // Spike Ball (Togepi)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_090 },  // Tiny Monkey (Pitheook)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_121 },  // Virtual (Porygon)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_122 },  // Weather (Castform)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_126_0] = //Waters around Sootopolis
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_042 },  // Seed (Sunkern)
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_043 },  // Cottonweed (Hoppip)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_044 },  // Rubber Fruit (Bounsweet)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_045 },  // Glowing Spore (Morelull)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_066 },  // Big Leaf (Chikorita)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_127_0] = //Waters south of Mossdeep, transitions back to land
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_047 },  // Matcha (Poltchageist)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_048 },  // Olive (Smoliv)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_049 },  // Cactus (Cacnea)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_068 },  // Penguin (Piplup)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_051 },  // Disasterous (Absol)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_128_0] = //Desert island outcropping (Contains Sandy Caves)
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_052 },  // Strong Bite (Poochyena)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_053 },  // Bonsai (Bonsly)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_054 },  // Shellfish (Kabuto)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_055 },  // Spiral (Omanyte)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_056 },  // Amber (Aerodactyl)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_129_0] = //Ocean waters south of desert
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_102 },  // Electric Eel (Tynamo)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_103 },  // Fire Anteater (Heatmor)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_104 },  // Armored Ant (Durant)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_105 },  // Desert Snek (Silicobra)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_106 },  // Living Canvas (Smeargle)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_130_0] = //Ocean route that contains mirage island
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_107 },  // Alluring (Mimikyu)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_108 },  // Barrier (Mime Jr)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_109 },  // Sleepy Bear (Komala)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_110 },  // Telekinesis (Elgyem)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_111 },  // Hovering (Gligar)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_131_0] = //Ocean route that contains sky pillar, to the right of Pacifilog East
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_112 },  // Sandstorm (Stunfisk)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_113 },  // Rolling (Rellor)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_114 },  // Sand Castle (Sandygast)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_115 },  // Burrowing (Sandile)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_116 },  // Mud Golem (Golett)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_132_0] = //Ocean route with a walking path, between the pacifilogs
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_117 },  // Scorch (Numel)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_118 },  // Bubbling (Slugma)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_119 },  // Candle (Litwick)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_120 },  // Fire Child (Charcadet)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_121 },  // Virtual (Porygon)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_133_0] = //Ocean route with a walking path, to the left of Pacifilog West
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_122 },  // Weather (Castform)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_123 },  // Frost (Snorunt)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_124 },  // Swine (Swinub)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_125 },  // Frost Acrobat (Sneasel)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_126 },  // Dolphin (Cetoddle)
        },
        .count = 5
    },
    
    [LOCATIONID_ROUTE_134_0] = //Route north of Pacifilog
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_127 },  // Frost (Bergmite)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_128 },  // Ice Dragon (Frigibax)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_129 },  // Screeching (Noibat)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_130 },  // Axe (Axew)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_131 },  // Sonic (Jangmo-o)
        },
        .count = 5
    },
    
    [LOCATIONID_METEORFALLS_0] = 
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_059 },  // Hard Head (Cranidos)
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_060 },  // Shield (Shieldon)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_063 },  // Royal Dino (Tyrunt)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_064 },  // Ice Sail (Amaura)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_062 },  // First Bird (Archen)
        },
        .count = 5
    },
    
    [LOCATIONID_RUSTURFTUNNEL_0] = 
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_054 },  // Shellfish (Kabuto)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_055 },  // Spiral (Omanyte)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_056 },  // Amber (Aerodactyl)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_053 },  // Bonsai (Bonsly)
        },
        .count = 4
    },
    
    [LOCATIONID_GRANITECAVE_0] = //Rocky cave with fighting types
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_036 },  // Pig Monkey (Mankey)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_037 },  // Thrusting Arm (Makuhita)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_038 },  // Lone Warrior (Falink)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_040 },  // Smirking Panda (Pancham)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_039 },  // Emanating (Riolu)
        },
        .count = 5
    },
    
    [LOCATIONID_PETALBURGWOODS_0] = //Grass and bug baby
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_009 },  // String Ball (Tarountula)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_050 },  // Acorn (Seedot)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_010 },  // Grasshopper (Nymble)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_041 },  // Hearty Spore (Shroomish)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_045 },  // Glowing Spore (Morelull)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_011 },  // Bagworm (Burmy)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_012 },  // Tiny Bee (Combee)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_048 },  // Olive (Smolive)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_004 },  // Ladybug (Ledyba)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_005 },  // Bee Fly (Cutiefly)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_013 },  // Larva (Blipbug)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_084 },  // Stump (Phantump)
        },
        .count = 9
    },

    [LOCATIONID_PETALBURGWOODS_1] = 
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_009 },  // String Ball (Tarountula)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_050 },  // Acorn (Seedot)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_010 },  // Grasshopper (Nymble)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_041 },  // Hearty Spore (Shroomish)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_045 },  // Glowing Spore (Morelull)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_011 },  // Bagworm (Burmy)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_012 },  // Tiny Bee (Combee)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_048 },  // Olive (Smolive)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_004 },  // Ladybug (Ledyba)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_005 },  // Bee Fly (Cutiefly)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_013 },  // Larva (Blipbug)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_084 },  // Stump (Phantump)
        },
        .count = 9
    },

    [LOCATIONID_PETALBURGWOODS_2] = 
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_009 },  // String Ball (Tarountula)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_050 },  // Acorn (Seedot)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_010 },  // Grasshopper (Nymble)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_041 },  // Hearty Spore (Shroomish)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_045 },  // Glowing Spore (Morelull)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_011 },  // Bagworm (Burmy)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_012 },  // Tiny Bee (Combee)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_048 },  // Olive (Smolive)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_004 },  // Ladybug (Ledyba)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_005 },  // Bee Fly (Cutiefly)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_013 },  // Larva (Blipbug)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_084 },  // Stump (Phantump)
        },
        .count = 9
    },
    
    [LOCATIONID_MTCHIMNEY_0] = //Lava pool mountaintop where Maxie did the thing
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_117 },  // Scorch (Numel)
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_079 },  // Bronze Plate (Bronzor)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_118 },  // Bubbling (Slugma)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_103 },  // Anteater (Heatmor)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_081 },  // Sword (Honedge)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_032 },   // Stomach (Gulpin)
        },
        .count = 6
    },

    [LOCATIONID_MTCHIMNEY_1] =
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_117 },  // Scorch (Numel)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_079 },  // Bronze Plate (Bronzor)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_118 },  // Bubbling (Slugma)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_103 },  // Anteater (Heatmor)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_081 },  // Sword (Honedge)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_119 },  // Candle (Litwick)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_083 },  // Gem (Sableye)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_120 },  // Fire Child (Charcadet)
        },
        .count = 8
    },

    [LOCATIONID_MTCHIMNEY_2] =
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_117 },  // Scorch (Numel)
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_079 },  // Bronze Plate (Bronzor)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_118 },  // Bubbling (Slugma)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_103 },  // Anteater (Heatmor)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_081 },  // Sword (Honedge)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_120 },  // Fire Child (Charcadet)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_080 },  // Iron Ball (Beldum)
        },
        .count = 7
    },
    
    [LOCATIONID_JAGGEDPASS_0] = //Ashy area covered in volcanic ash
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_115 },  // Desert Croc (Sandile)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_112 },  // Mud Trap (Stunfisk)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_113 },  // Rolling (Rellor)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_116 },  // Automaton (Golett)
        },
        .count = 4
    },
    
    [LOCATIONID_JAGGEDPASS_1] = // Lake formed near volcaino
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 50, .fossilItemId = ITEM_POKEFOSSIL_092 },  // Common Fish (Basculin)
            { .chance = 50, .fossilItemId = ITEM_POKEFOSSIL_093 },  // Bullet Jet (Remoraid)
        },
        .count = 2
    },

    [LOCATIONID_FIERYPATH_0] = //Hot path near volcano
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 40, .fossilItemId = ITEM_POKEFOSSIL_118 },  // Lava (Slumga)
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_016 },  // Radiator (Sizzilipede)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_117 },  // Magma Geode (Numel)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_120 },  // Fire Child (Charcadet)
        },
        .count = 4
    },
    
    [LOCATIONID_MTPYRE_0] = // Ghost mountain
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_082 },  // Puppet (Shuppet)
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_083 },  // Gem (Sableye)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_085 },  // Skull (Duskull)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_086 },  // Vocal Cord (Misdreavus)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_107 },  // Disguised (Mimikyu)
        },
        .count = 5
    },
    
    [LOCATIONID_VICTORYROAD_0] = 
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_127 },  // Ice Chunk (Bergmite)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_128 },  // Ice Fin (Frigibax)
            { .chance = 18, .fossilItemId = ITEM_POKEFOSSIL_129 },  // Bat Ear (Noibat)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_130 },  // Tusk (Axew)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_131 },  // Scaly (Jangmo-o)
            { .chance = 4, .fossilItemId = ITEM_POKEFOSSIL_067 },  // Fire Pig (Tepig)
            { .chance = 4, .fossilItemId = ITEM_POKEFOSSIL_068 },  // Penguin (Piplup)
            { .chance = 4, .fossilItemId = ITEM_POKEFOSSIL_066 },  // Big Leaf (Chikorita)
        },
        .count = 7
    },
    
    [LOCATIONID_SHOALCAVE_0] = //Ice caves
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_097 },  // Sea Slug (Shellos)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_098 },  // Ugly Fish (Feebas)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_091 },  // Heart (Luvdisk)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_126 },  // Tundra Whale (Cetoddle)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_123 },  // Snow Hat (Snorunt)
        },
        .count = 5
    },
    
    [LOCATIONID_SKYPILLAR_0] = //Dragons
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_129 },  // Screeching (Noibat)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_008 },  // Mantis (Scyther)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_075 },  // Tiny Metal Bird (Rookidee)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_018 },  // Odd Duck (Farfetchd)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_087 },  // Tiny Birdbrain (Natu)
        },
        .count = 5
    },
    
    [LOCATIONID_MIRAGETOWER_0] = //Prob psychic types
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_050 },  // Seedling (Seedot)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_115 },  // Desert Croc (Sandile)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_114 },  // Sand Heap (Sandygast)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_052 },  // Bite (Poochyena)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_017 },  // Hairy Bug (Weedle)
        },
        .count = 5
    },
    
    [LOCATIONID_SANDYCAVES_0] = //Ground types galore
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_112 },  // Mud Trap (Stunfisk)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_113 },  // Rolling (Rellor)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_105 },  // Sand Snake (Silicobra)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_049 },  // Cactus (Cacnea)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_043 },  // Floating Grass (Hoppip)
        },
        .count = 5
    },
    
    [LOCATIONID_NEWMAUVILLE_0] = //Electric generater zone
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 35, .fossilItemId = ITEM_POKEFOSSIL_014 },  // Attached (Joltik)
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_072 },  // Lightning (Electrike)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_073 },  // Thunderbolt (Blitzle)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_069 },  // Cheering + (Plusle)
            { .chance = 5, .fossilItemId = ITEM_POKEFOSSIL_070 },  // Cheering - (Minun)
        },
        .count = 5
    },
    
    [LOCATIONID_ABANDONEDSHIP_0] = //Water types and ghosts
    {
        .fossils = (const struct LocSysFossilData[]) {
            { .chance = 30, .fossilItemId = ITEM_POKEFOSSIL_099 },  // Big Catfish (Dondozo)
            { .chance = 25, .fossilItemId = ITEM_POKEFOSSIL_100 },  // Nigiri Sushi (Tatsugiri)
            { .chance = 20, .fossilItemId = ITEM_POKEFOSSIL_101 },  // Kelp (Skrelp)
            { .chance = 15, .fossilItemId = ITEM_POKEFOSSIL_081 },  // Sword (Honedge)
            { .chance = 10, .fossilItemId = ITEM_POKEFOSSIL_080 },  // Iron Ball (Beldum)
        },
        .count = 5
    },
};

#endif // GUARD_MINING_LOCATION_DATA_H
    