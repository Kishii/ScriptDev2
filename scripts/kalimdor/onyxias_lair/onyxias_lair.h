/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_ONYXIA_H
#define DEF_ONYXIA_H

enum
{
    TYPE_ONYXIA                 = 0,

    NPC_ONYXIA_TRIGGER          = 12758
};

class instance_onyxias_lair : public ScriptedInstance
{
    public:
        instance_onyxias_lair(Map* pMap);
        ~instance_onyxias_lair() {}

        void Initialize();

        void OnCreatureCreate(Creature* pCreature);

        uint64 GetOnyxiaTriggerGUID() const { return m_uiOnyxTriggerGUID; }
        bool IsEncounterInProgress() const { return m_uiOnyxiaState == IN_PROGRESS; }

        const char* Save() { return m_strInstData.c_str(); }
        void Load(const char* chrIn);

        uint32 GetData(uint32 uiType);
        void SetData(uint32 uiType, uint32 uiData);
    protected:
        uint64 m_uiOnyxTriggerGUID;
        uint32 m_uiOnyxiaState;
        std::string m_strInstData;
};

#endif
