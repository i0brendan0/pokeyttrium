# Pokemon Yttrium

## What is this hack

This hack has a completely new region based off of Scandinavia.
    (Region map soon)

## Features

### pokeemerald Expansion features

    - Generation 4 through 8 Pokemon (Excluding LA Pokemon)
    - Fairy Type
    - Physical/Special/Status Category Split.
    - New moves and abilities up to Sword/Shield.
    - Updates National Dex incorporating all Generation 4 through 8 species.
    - Base stats have been updated.
        - Rotom's normal form has modified base stats.
    - New evolution methods.
    - Hidden Abilities.
    - Items from newer generations.
    - TMs are reusable.
    - Stats that change from a Pokemon's nature will be shaded.

### New Features

    - The unused ability Cacophony has been re-added as an alternative to Punk Rocker. (Potentially remove)
        - Pokemon with Cacophony do 1.5x damage with sound-based moves.
        - Pokemon with Cacophony will get a 10% boost to accuracy with sound-based moves.
        - The Whismur and Kricketot line have Cacophony as their second ability. 
    - Pokemon that evolve by trade can now evolve through the use of a Link Cable. (Potentially remove)
    - Pokemon that evolve by trade while holding an item can now evolve through the use of a Link Cable while holding that item. (Potentially remove)
    - Phione evolves into Manaphy at high friendship.
    - Certain moves have changes in type and/or effect.
        - Splash
            - Water
            - Does damage during rain based on the user's weight.
        - Cut
            - High critical hit ratio.
        - Strength
            - 20% chance to flinch
    - Swarming Pokemon may now hold special items.
        - (Implemented but no items yet.)
    - Castform gets a Sandy Form.
        - (Implemented but no sprite yet)
    - Hidden Trees. Hidden Grotto-like interactable trees where each day, a Pokemon or item may drop from the tree.
        - All Hidden Tree Pokemon will have their hidden ability. 
        - (Implemented but no Pokemon to obtain yet.)
    - Certain Pokemon will know moves as a baby just like Pichu and Volt Tackle. 
        - Farfetch'd - Leek - Sky Attack
        - Chansey/Happiny - Lucky Punch - Mach Punch
        - Cubone - Thick Club - Bone Rush
        - Sneasel - Razor Claw - Night Slash
        - Gligar - Razor Fang - Leech Life
        - Clamperl - Deep Sea Scale - Psychic
        - Clamperl - Deep Sea Tooth - Crunch
        - Horsea - Dragon Scale - Dragon Breath
        - Elekid - Electirizer - Discharge
        - Magby - Magmarizer - Lava Plume
        - Rhydon - Protector - Head Smash
        - Duskull - Reaper Cloth - Ominous Wind
        - Feebas - Prism Scale - Aqua Jet
        - Check Gen 5-8 Pokemon
    - New low-hp type abilities.
    - A baby egg lotto will be available. Basically an updated Odd Egg.
        - All baby Pokemon will be available in the egg, including a special bonus that has a 2% chance of occuring.
        - Pokemon hatched from the egg have a 16% chance of being shiny.
        - Talk to the egg lady in ___ after entering the Hall of Fame.
            - You'll get a new egg each time you beat the Champion.
    - Upon entering the Hall of Fame for the first time, certain locations may have their wild Pokemon change.
        - Will mostly allow non-native Pokemon to be available without jamming them into post-game locations.
    - 18 trainers are scattered throughout Hoenn, one for each type. Defeating them will give a bonus to damage done by their type.
        - (Implemented but no trainers available yet.)
    - Trainers may give out items after being beaten in a rematch.

### A new set of TMs - Up to 200 - Check [here](pokeyttrium/blob/master/info/TM.md) for locations

    List TBD.

### New Pokemon -  Check [here](info/BETAMON.md)

    - Beta mon from previous generations.
    - New incense items for use with beta baby mon.
        - Luck Incense - Meowsy
        - Flame Incense - Trifox/Minicorn/Puddi
            - . (Charcoal)
        - Grime Incense - Grimey
            - . (Poison Barb)
        - Grass Incense - Tangel/Para
        - Sea Incense - Golpy
        - Full Incense - Dunslet
        - Lax Incense - Chiks

### TODO LIST

    - TMs 1-200 need descriptions.
        - Use move descriptions as a base.
    - New incense items need graphics.
    - Implement new swarms along with held items.
    - Give out Oval Charm and Shiny Charm.
    - Add recurring items. (Both regular and hidden)
    - Modify TM prices
    - Remove a lot of Generation configurations.
    - EV training items give EVs when walking.
    - Maybe modify how badly poisoned works.
    - Redo Pickup Table again. src/battle_script_commands.c
    - Add in placeholder overworld data for new Pokemon.
    - Check gen 5-8 Pokemon to give new abilities.
    - Pokeemerald Tutorials
        - TM Case https://www.pokecommunity.com/showpost.php?p=10378278
        - One-time Shops https://www.pokecommunity.com/showpost.php?p=10133566&postcount=55
        - Faster text https://www.pokecommunity.com/showpost.php?p=10400198
        - See switch mon https://github.com/pret/pokeemerald/wiki/Show-Species-That-You're-Switching-For-in-the-Party-Menu
        - HM Items https://www.pokecommunity.com/threads/simple-modifications-directory.416647/page-15#post-10386496
        - Earn BP https://www.pokecommunity.com/threads/simple-modifications-directory.416647/page-16#post-10422051
        - Triple layer metatiles https://github.com/pret/pokeemerald/wiki/Triple-layer-metatiles
        - Rival name https://www.pokecommunity.com/threads/simple-modifications-directory.416647/page-8#post-10211189

## Changes

### Changes from Emerald

    - Shiny odds have been increase by 2x.
    - Pokemon can get 255 EVs in each stat similar to STAT EXP in generation 1 and 2.
    - Pure Power now doubles Special Attack instead of Attack. To differentiate from Huge Power.
    - Minus now raises Attack instead of Special Attack. To differentiate from Plus.
    - Castform shows its shiny color when transformed.
    - Obedience is increased with each badge.
    - Pickup table has been modified.
        - Due to this change and that plenty of useful items are now possible to get from Pickup, some pokemon get the Pickup ability.
            - Vulpix line
            - Plusle and Minun
            - Starly
            - Manaphy and Phione
            - Check Gen 5-8 Pokemon
    - More bag space. 100 spots now.
    - More PC space. 100 spots now.
    - Rose Incense has been renamed. It's now called the Grass Incense.
    - Starting money has been changed to 5000.
    - Cut trees will no longer reappear.
    - Rock Smash rocks blocking an area will no longer appear.
        - Temporary rocks will be added to allow Rock Smash encounters.
    - Pokeballs may give out more than 1 item.
        - Potions, Repels, Pokeballs, Battle Boost Items - 5
        - Super Potions, Super Repels, Great Balls, Shards, Escape Ropes, Single Status Healing Items - 3
        - Ethers, Elixirs, Specialty Balls, Revives, Full Heals, Bitter Recovery Items (not including Revival Herb) - 2
    - If a Pokemon has their hidden ability, it will be highlighted in the summary screen.

### Type Changes -  Check [here](info/TYPE_CHANGES.md) for Pokemon type changes.

    - Ice resists Dragon
    - Ice resists Ground
    - Steel is weak to Electric
    - Bug is neutral to Fairy
    - Bug resists Psychic
    - Bug is weak to Poison (Gen 1)

### pokeemerald Expansion configuration changes

    - Critical hits do 2x damage instead of 1.5x.
    - Trainers give boosted EXP compared to wild Pokemon.
    - Pokemon receive split EXP instead of full EXP if multiple participated.
    - Pokemon do not get a bonus to EXP when above the level they would evolve at.
    - Obtained badges boost stats.
    - Binding damage does 1/16th damage each turn instead of 1/8th.
    - Hidden Power uses IVs to determine power.
    - Rough Skin/Iron Barb damage is 1/16th instead of 1/8th.
    - Dark Type Pokemon are no longer immune to moves affected by Prankster. Dark types just nullify the priority boost.
    - Roost will make a pure Flying-type Pokemon typless instead of Normal.
    - Binding moves last for 2-5 turns instead of 4-5 turns.
    - Uproar lasts for 2-5 turns instead of 3 turns.
    - Hi-Jump Kick does recoil damage based on the damage done, not a flat amount based off the user's HP.
    - Conversion picks a move at random instead of only the first move.
    - Spite reduces PP by 2-5 instead of 4.
    - Sheer Cold has normal accuracy if the user is not Ice type.
    - Rapid Spin does not increase speed.
    - Minimize only increases evasion by 1 stage instead of 2.
    - Hi-Jump Kick will not recoil if the target is immune.
        - My reasoning is they still hit the target but it does no damage.
    - Damaging healing moves won't heal the user that's under the effect of Heal Block.
        - The move will still damage the opponent.
    - Teleport functions normally instead of allowing the user to switch out.
    - Dark Void will not fail if used by any Pokemon besides Darkrai.
    - Weather abilities will last until the weather is changed instead of 5 turns.
    - Nest Ball's catch rate is based off of Gen 5.
    - Sport Ball has a catch rate of 1.5x instead of 1x.
    - Serene Grace will not boost the chance of flinching from Razor Fang or King's Rock.
    - Health recovery items heal as they would pre-Gen 7.
    - Incense items work for breeding as they would normally instead of having no effect.
        - New items will be added for use with Beta Mon.

### Notable Bug Fixes

    - RNG will now be seeded like it should.
    - Pokedex entries will not show without the Pokedex.
    - Various map edits that involve incorrectly used tiles.
    - New swarms will generate correctly. (Hopefully)
    - Kadabra will not evolve while holding an everstone.

### Shiny Color Changes

    - PENDING
        - Abra
        - Articuno
        - Blissey
        - Burmy (All forms)
        - Chingling
        - Combusken
        - Diglett
        - Dugtrio
        - Elekid
        - Gabite
        - Gastrodon
        - Gengar
        - Igglybuff
        - Kadabra
        - Kangaskhan
        - Leafeon
        - Mantyke
        - Meowth
        - Nidoqueen
        - Persian
        - Pichu
        - Pikachu
        - Plusle
        - Poliwag
        - Poliwhirl
        - Scyther
        - Shellos
        - Skitty
        - Smoochum
        - Snorlax
        - Sunkern
        - Togepi
        - Togetic
        - Venonat
        - Wormadam (All forms)
        - Zapdos
        - Check Gen 5-8 Pokemon

Use x_MODIFY_x to find changes for future.

### [List of pokeemerald Expansion contributors](https://github.com/rh-hideout/pokeemerald-expansion/wiki/Credits)
