//
//  state.h
//  cpp
//
//  Created by Bob Nystrom on 7/13/13.
//  Copyright (c) 2013 Bob Nystrom. All rights reserved.
//

#ifndef cpp_state_h
#define cpp_state_h

namespace State
{
    enum Input
    {
        PRESS_A,
        PRESS_B,
        PRESS_LEFT,
        PRESS_RIGHT,
        PRESS_DOWN,
        RELEASE_A,
        RELEASE_DOWN,
    };

    enum Animate
    {
        IMAGE_JUMP,
        IMAGE_DUCK,
        IMAGE_STAND,
        IMAGE_DIVE
    };

    static const int JUMP_VELOCITY = 1;
    static const int MAX_CHARGE = 10;

    namespace Spaghetti1
    {
        class Heroine
        {
        public:
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }
            void handleInput(Input input);
            double yVelocity_;
        };

        //^spaghetti-1
        void Heroine::handleInput(Input input)
        {
            if (input == PRESS_B)
            {
                yVelocity_ = JUMP_VELOCITY;
                setGraphics(IMAGE_JUMP);
            }
        }
        //^spaghetti-1
    }

    namespace Spaghetti2
    {
        class Heroine
        {
        public:
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }
            void handleInput(Input input);
            double yVelocity_;
            bool isJumping_;
        };

        //^spaghetti-2
        void Heroine::handleInput(Input input)
        {
            if (input == PRESS_B)
            {
                if (!isJumping_)
                {
                    isJumping_ = true;
                    // Jump...
                }
            }
        }
        //^spaghetti-2
    }

    namespace Spaghetti3
    {
        class Heroine
        {
        public:
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }
            void handleInput(Input input);
            double yVelocity_;
            bool isJumping_;
        };

        //^spaghetti-3
        void Heroine::handleInput(Input input)
        {
            if (input == PRESS_B)
            {
                // Jump if not jumping...
            }
            else if (input == PRESS_DOWN)
            {
                if (!isJumping_)
                {
                    setGraphics(IMAGE_DUCK);
                }
            }
            else if (input == RELEASE_DOWN)
            {
                setGraphics(IMAGE_STAND);
            }
        }
        //^spaghetti-3
    }

    namespace Spaghetti4
    {
        class Heroine
        {
        public:
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }
            void handleInput(Input input);
            double yVelocity_;
            bool isJumping_;
            bool isDucking_;
        };

        //^spaghetti-4
        void Heroine::handleInput(Input input)
        {
            if (input == PRESS_B)
            {
                if (!isJumping_ && !isDucking_)
                {
                    // Jump...
                }
            }
            else if (input == PRESS_DOWN)
            {
                if (!isJumping_)
                {
                    isDucking_ = true;
                    setGraphics(IMAGE_DUCK);
                }
            }
            else if (input == RELEASE_DOWN)
            {
                if (isDucking_)
                {
                    isDucking_ = false;
                    setGraphics(IMAGE_STAND);
                }
            }
        }
        //^spaghetti-4
    }

    namespace Spaghetti5
    {
        class Heroine
        {
        public:
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }
            void handleInput(Input input);
            double yVelocity_;
            bool isJumping_;
            bool isDucking_;
        };

        //^spaghetti-5
        void Heroine::handleInput(Input input)
        {
            if (input == PRESS_B)
            {
                if (!isJumping_ && !isDucking_)
                {
                    // Jump...
                }
            }
            else if (input == PRESS_DOWN)
            {
                if (!isJumping_)
                {
                    isDucking_ = true;
                    setGraphics(IMAGE_DUCK);
                }
                else
                {
                    isJumping_ = false;
                    setGraphics(IMAGE_DIVE);
                }
            }
            else if (input == RELEASE_DOWN)
            {
                if (isDucking_)
                {
                    // Stand...
                }
            }
        }
        //^spaghetti-5
    }

    namespace FSM
    {
        //^enum
        enum State
        {
            STATE_STANDING,
            STATE_JUMPING,
            STATE_DUCKING,
            STATE_DIVING
        };
        //^enum

        class Heroine
        {
        public:
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }
            void superBomb()
            {
            }
            void handleInput(Input input);
            void update();
            double yVelocity_;
            State state_;
            int chargeTime_;

            void startDucking()
            {
                Input input = PRESS_DOWN;

                //^start-ducking
                // In standing state:
                if (input == PRESS_DOWN)
                {
                    // Change state...
                    chargeTime_ = 0;
                    setGraphics(IMAGE_DUCK);
                }
                //^start-ducking
            }
        };

        //^state-switch
        void Heroine::handleInput(Input input)
        {
            switch (state_)
            {
            case STATE_STANDING:
                if (input == PRESS_B)
                {
                    state_ = STATE_JUMPING;
                    yVelocity_ = JUMP_VELOCITY;
                    setGraphics(IMAGE_JUMP);
                }
                else if (input == PRESS_DOWN)
                {
                    state_ = STATE_DUCKING;
                    setGraphics(IMAGE_DUCK);
                }
                break;

            case STATE_JUMPING:
                if (input == PRESS_DOWN)
                {
                    state_ = STATE_DIVING;
                    setGraphics(IMAGE_DIVE);
                }
                break;

            case STATE_DUCKING:
                if (input == RELEASE_DOWN)
                {
                    state_ = STATE_STANDING;
                    setGraphics(IMAGE_STAND);
                }
                break;
                //^omit
            case STATE_DIVING:
                break;
                //^omit
            }
        }

        //^state-switch

        //^switch-update
        void Heroine::update()
        {
            if (state_ == STATE_DUCKING)
            {
                chargeTime_++;
                if (chargeTime_ > MAX_CHARGE)
                {
                    superBomb();
                }
            }
        }
        //^switch-update
    }

    namespace FSMChargeTime
    {
        //^enum
        enum State
        {
            STATE_STANDING,
            STATE_JUMPING,
            STATE_DUCKING,
            STATE_DIVING
        };
        //^enum

        class Heroine
        {
        public:
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }
            void superBomb()
            {
            }
            void handleInput(Input input);
            double yVelocity_;
            State state_;
            int chargeTime_;
        };

        //^state-switch-reset
        void Heroine::handleInput(Input input)
        {
            switch (state_)
            {
            case STATE_STANDING:
                if (input == PRESS_DOWN)
                {
                    state_ = STATE_DUCKING;
                    chargeTime_ = 0;
                    setGraphics(IMAGE_DUCK);
                }
                // Handle other inputs...
                break;

                // Other states...
                //^omit
            case STATE_JUMPING:
            case STATE_DUCKING:
            case STATE_DIVING:
                break;
                //^omit
            }
        }
        //^state-switch-reset
    }

    namespace StatePattern
    {
        class Heroine;
        class JumpingState;

        //^heroine-state
        class HeroineState
        {
        public:
            //^omit
            static JumpingState jumping;
            //^omit
            virtual ~HeroineState()
            {
            }
            virtual void handleInput([[maybe_unused]] Heroine& heroine, [[maybe_unused]] Input input)
            {
            }
            virtual void update([[maybe_unused]] Heroine& heroine)
            {
            }
        };
        //^heroine-state

        class JumpingState : public HeroineState
        {
        };

        class StandingState;

        //^gof-heroine
        class Heroine
        {
            //^omit
            friend class StandingState;
            friend class JumpingState;
            //^omit
        public:
            virtual void handleInput(Input input)
            {
                state_->handleInput(*this, input);
            }

            virtual void update()
            {
                state_->update(*this);
            }

            // Other methods...
            //^omit
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }
            void superBomb()
            {
            }
            //^omit
        private:
            HeroineState* state_;
            //^omit
            double yVelocity_;
            //^omit
        };
        //^gof-heroine

        //^ducking-state
        class DuckingState : public HeroineState
        {
        public:
            DuckingState()
                : chargeTime_(0)
            {
            }

            virtual void handleInput(Heroine& heroine, Input input)
            {
                if (input == RELEASE_DOWN)
                {
                    // Change to standing state...
                    heroine.setGraphics(IMAGE_STAND);
                }
            }

            virtual void update(Heroine& heroine)
            {
                chargeTime_++;
                if (chargeTime_ > MAX_CHARGE)
                {
                    heroine.superBomb();
                }
            }

        private:
            int chargeTime_;
        };
        //^ducking-state
    }

    namespace InstancedStates
    {
        class Heroine;

        class HeroineState
        {
        public:
            virtual ~HeroineState()
            {
            }
            virtual HeroineState* handleInput([[maybe_unused]] Heroine& heroine, [[maybe_unused]] Input input)
            {
                return nullptr;
            }
            virtual void update([[maybe_unused]] Heroine& heroine)
            {
            }
        };

        class Heroine
        {
        public:
            virtual void handleInput(Input input);

        private:
            HeroineState* state_;
        };

        class DuckingState : public HeroineState
        {
        };

        //^swap-instance
        void Heroine::handleInput(Input input)
        {
            HeroineState* state = state_->handleInput(*this, input);
            if (state != nullptr)
            {
                delete state_;
                state_ = state;
            }
        }
        //^swap-instance

        class StandingState : public HeroineState
        {
        public:
            virtual HeroineState* handleInput(Heroine& heroine, Input input);
        };

        //^duck
        HeroineState* StandingState::handleInput([[maybe_unused]] Heroine& heroine, [[maybe_unused]] Input input)
        {
            if (input == PRESS_DOWN)
            {
                // Other code...
                return new DuckingState();
            }

            // Stay in this state.
            return nullptr;
        }
        //^duck
    }

    namespace StaticStateInstances
    {
        class StandingState;
        class DuckingState;
        class JumpingState;
        class DivingState;

        //^heroine-static-states
        class HeroineState
        {
        public:
            static StandingState standing;
            static DuckingState ducking;
            static JumpingState jumping;
            static DivingState diving;

            // Other code...
        };
        //^heroine-static-states

        class Heroine
        {
            friend class JumpingState;

        public:
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }
            void changeState([[maybe_unused]] HeroineState* state)
            {
            }

        private:
            HeroineState* state_;
        };

        class StandingState : public HeroineState
        {
        };
        class DuckingState : public HeroineState
        {
        };

        class JumpingState : public HeroineState
        {
            void handleInput(Heroine& heroine, Input input)
            {
                //^jump
                if (input == PRESS_B)
                {
                    heroine.state_ = &HeroineState::jumping;
                    heroine.setGraphics(IMAGE_JUMP);
                }
                //^jump
            }
        };
        class DivingState : public HeroineState
        {
        };
    }

    namespace EnterActionsBefore
    {
        class HeroineState
        {
        };

        class Heroine
        {
            friend class JumpingState;

        public:
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }
            void changeState([[maybe_unused]] HeroineState* state)
            {
            }
        };

        class StandingState : public HeroineState
        {
        };
        class DuckingState : public HeroineState
        {
        public:
            HeroineState* handleInput(Heroine& heroine, Input input);
        };

        //^enter-standing-before
        HeroineState* DuckingState::handleInput(Heroine& heroine, Input input)
        {
            if (input == RELEASE_DOWN)
            {
                heroine.setGraphics(IMAGE_STAND);
                return new StandingState();
            }

            // Other code...
            //^omit
            return nullptr;
            //^omit
        }
        //^enter-standing-before
    }

    namespace EnterActions
    {
        class Heroine;

        class HeroineState
        {
        public:
            virtual ~HeroineState()
            {
            }
            virtual void enter([[maybe_unused]] Heroine& heroine)
            {
            }
            virtual HeroineState* handleInput([[maybe_unused]] Heroine& heroine, [[maybe_unused]] Input input)
            {
                return nullptr;
            }
        };

        class Heroine
        {
        public:
            void handleInput(Input input);
            void setGraphics([[maybe_unused]] Animate animate)
            {
            }

        private:
            HeroineState* state_;
        };

        //^standing-with-enter
        class StandingState : public HeroineState
        {
        public:
            virtual void enter(Heroine& heroine)
            {
                heroine.setGraphics(IMAGE_STAND);
            }

            // Other code...
        };
        //^standing-with-enter

        //^change-state
        void Heroine::handleInput(Input input)
        {
            HeroineState* state = state_->handleInput(*this, input);
            if (state != nullptr)
            {
                delete state_;
                state_ = state;

                // Call the enter action on the new state.
                state_->enter(*this);
            }
        }
        //^change-state

        class DuckingState : public HeroineState
        {
        public:
            virtual HeroineState* handleInput(Heroine& heroine, Input input);
        };

        //^enter-standing
        HeroineState* DuckingState::handleInput([[maybe_unused]] Heroine& heroine, [[maybe_unused]] Input input)
        {
            if (input == RELEASE_DOWN)
            {
                return new StandingState();
            }

            // Other code...
            //^omit
            return nullptr;
            //^omit
        }
        //^enter-standing
    }

    namespace Concurrent
    {
        class Heroine;

        class HeroineState
        {
        public:
            void handleInput([[maybe_unused]] Heroine& heroine, [[maybe_unused]] Input input)
            {
            }
        };

        //^two-states
        class Heroine
        {
            // Other code...
            //^omit
            virtual void handleInput(Input input);
            //^omit

        private:
            HeroineState* state_;
            HeroineState* equipment_;
        };
        //^two-states

        //^handle-two-inputs
        void Heroine::handleInput(Input input)
        {
            state_->handleInput(*this, input);
            equipment_->handleInput(*this, input);
        }
        //^handle-two-inputs
    }

    namespace Hsm
    {
        class Heroine;

        class HeroineState
        {
        public:
            virtual void handleInput(Heroine& heroine, Input input);
        };

        class Heroine
        {
            void handleInput([[maybe_unused]] Input input)
            {
            }

        private:
            HeroineState* state_;
        };

        //^on-ground
        class OnGroundState : public HeroineState
        {
        public:
            virtual void handleInput([[maybe_unused]] Heroine& heroine, Input input)
            {
                if (input == PRESS_B)
                {
                    // Jump...
                }
                else if (input == PRESS_DOWN)
                {
                    // Duck...
                }
            }
        };
        //^on-ground

        //^duck-on-ground
        class DuckingState : public OnGroundState
        {
        public:
            virtual void handleInput(Heroine& heroine, Input input)
            {
                if (input == RELEASE_DOWN)
                {
                    // Stand up...
                }
                else
                {
                    // Didn't handle input, so walk up hierarchy.
                    OnGroundState::handleInput(heroine, input);
                }
            }
        };
        //^duck-on-ground
    }
}

#endif
