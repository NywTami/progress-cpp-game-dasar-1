#ifndef STATUS_EFFECT_H
#define STATUS_EFFECT_H

#include <string>
#include <utility>

// Effect type controls whether value is added or subtracted from a stat.
enum class EffectType {
    Buff,
    Debuff
};

enum class TargetStat {
    AttackPercent,
    DefensePoints
};

struct StatusEffect {
    std::string name;
    EffectType type;
    TargetStat target_stat;
    int value;
    int remaining_turns;
    bool dispellable;

    StatusEffect(std::string effect_name, EffectType effect_type,
                 TargetStat stat, int effect_value, int duration,
                 bool can_dispel = true)
        : name(std::move(effect_name)), type(effect_type), target_stat(stat),
          value(effect_value), remaining_turns(duration), dispellable(can_dispel) {}
};

#endif
