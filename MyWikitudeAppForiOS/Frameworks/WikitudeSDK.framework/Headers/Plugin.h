//
// Created by simon on 08/04/15.
// Copyright (c) 2015 Wikitude. All rights reserved.
//


#ifndef PLUGIN_H_
#define PLUGIN_H_

#ifdef __cplusplus

#include <list>
#include <string>
#include <memory>


namespace wikitude { namespace sdk {
    
    namespace impl {

        class Frame;
        class RecognizedTarget;
        
        class Plugin {
            
        public:

            /**
             * Constructor, pass a unique identifier for each of your plugins.
             */
            Plugin(std::string identifier_);

            virtual ~Plugin();
            
            /**
             * Will be called once after your Plugin was successfully added to the Wikitude Engine. Initialize your plugin here.
             */
            virtual void initialize();

            /**
             * Will be called every time the Wikitude Engine pauses.
             */
            virtual void pause();
            
            /**
             * Will be called when the Wikitude Engine starts for the first time and after every pause.
             * 
             * @param pausedTime_ the duration of the pause in milliseconds
             */
            virtual void resume(unsigned int pausedTime_);

            /**
             * Will be called every time the SDK surface size changes.
             * It is also called right after the plugin is initialzed.
             */
            virtual void surfaceChanged(int width, int height);

            /**
             * Will be called when the Wikitude Engine shuts down.
             */
            virtual void destroy();

            /**
             * Will be called every time the Wikitude Enigine receives a new camera frame from the platform camera.
             *
             * @param cameraFrame_ frame wrapper object which contains the frame data and some metadata about the frame
             */
            virtual void cameraFrameAvailable(const Frame& cameraFrame_) = 0;

            /**
             * Will be called after every image recognition cycle.
             *
             * @param recognizedTargets_ list of recognized targets, empty if no target was recognized
             */
            virtual void update(const std::list<RecognizedTarget>& recognizedTargets_) = 0;
            
            /**
             * Will be called before any Wikitude SDK internal rendering is done. Therefore any drawn objects are behind any Wikitude SDK object.
             */
            virtual void startRender();
            
            /**
             * Will be called right after any Wikitude SDK internal rendering is done. Therefore any drawn objects are in front of any Wikitude SDK object.
             */
            virtual void endRender();

            /**
             * By default only black and white frame data will be passed to the cameraFrameAvailable method, if you need color data override this method and return true.
             */
            virtual bool processesColorCameraFrames();

            /**
             * Use this method to enqueue JavaScript calls that are evaluated in the upcoming frame.
             * Note: This method is only available when using the Wikitude Architect SDK (JS API).
             */
            void addToJavaScriptQueue(const std::string& javaScriptSnippet_);
            
            /**
             * Method used internally to get all pending JavaScript calls and execute them in the Wikitude Architect SDK (JS API) web view context.
             */
            std::list<std::string>& getJavaScriptQueue();

            /**
             * Returns the identifier of this particular plugin.
             */
            const std::string& getIdentifier() const;

            /**
             * Set's this plugin enabled or not. A enabled plugin receives cameraFrameAvailable, update, startRender and endRender calls. 
             */
            virtual void setEnabled(bool _enabled);
            
            /**
             * Return the enabled state of this particular plugin.
             */
            virtual bool isEnabled() const;
            
        private:
            std::string     _identifier;
            bool            _enabled;

            std::list<std::string> _javaScriptQueue;
        };
    }
    using impl::Plugin;    
}}

#endif /* __cplusplus */

#endif //__Plugin_H_
