/*
 * Copyright 2009-2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <esnpapi.h>

#include <org/w3c/dom.h>

class EventHandler;

class TestInstance: public PluginInstance
{
    EventHandler* downHandler;
    org::w3c::dom::Document* document;

    void initialize();
    void drawCharts(org::w3c::dom::Document* document);

public:
    TestInstance(NPP npp, NPObject* window) :
        PluginInstance(npp, window),
        downHandler(0),
        document(0)
    {
        initialize();
    }
    ~TestInstance();

    void down(org::w3c::dom::events::Event* evt);
};

class EventHandler : public org::w3c::dom::events::EventListener
{
    TestInstance* instance;
    void (TestInstance::*handler)(org::w3c::dom::events::Event* evt);

public:
    EventHandler(TestInstance* instance, void (TestInstance::*handler)(org::w3c::dom::events::Event* evt)) :
        instance(instance),
        handler(handler)
    {
    }
    virtual void handleEvent(org::w3c::dom::events::Event* evt)
    {
        (instance->*handler)(evt);
    }
    unsigned int retain()
    {
        return instance->retain(this);
    };
    unsigned int release()
    {
        return instance->release(this);
    };
};


#endif // TEST_H_INCLUDED