//
//  command.h
//  cpp
//
//  Created by Bob Nystrom on 10/7/13.
//  Copyright (c) 2013 Bob Nystrom. All rights reserved.
//

#ifndef cpp_command_h
#define cpp_command_h

namespace CommandPattern
{
    enum Button
    {
        BUTTON_UP,
        BUTTON_DOWN,
        BUTTON_LEFT,
        BUTTON_RIGHT,
        BUTTON_X,
        BUTTON_Y,
        BUTTON_A,
        BUTTON_B
    };

    bool isPressed([[maybe_unused]] Button button)
    {
        return false;
    }
    void jump()
    {
    }
    void fireGun()
    {
    }
    void swapWeapon()
    {
    }
    void lurchIneffectively()
    {
    }

    namespace BeforeCommand
    {
        class InputHandler
        {
        public:
            void handleInput();
        };

        //^handle-input
        void InputHandler::handleInput()
        {
            if (isPressed(BUTTON_X))
                jump();
            else if (isPressed(BUTTON_Y))
                fireGun();
            else if (isPressed(BUTTON_A))
                swapWeapon();
            else if (isPressed(BUTTON_B))
                lurchIneffectively();
        }
        //^handle-input
    }

    namespace InputHandlingCommand
    {
        //^command
        class Command
        {
        public:
            virtual ~Command()
            {
            }
            virtual void execute() = 0;
        };
        //^command

        //^command-classes
        class JumpCommand : public Command
        {
        public:
            virtual void execute()
            {
                jump();
            }
        };

        class FireCommand : public Command
        {
        public:
            virtual void execute()
            {
                fireGun();
            }
        };

        // You get the idea...
        //^command-classes

        //^input-handler-class
        class InputHandler
        {
        public:
            void handleInput();

            // Methods to bind commands...

        private:
            Command* buttonX_;
            Command* buttonY_;
            Command* buttonA_;
            Command* buttonB_;
        };
        //^input-handler-class

        //^handle-input-commands
        void InputHandler::handleInput()
        {
            if (isPressed(BUTTON_X))
                buttonX_->execute();
            else if (isPressed(BUTTON_Y))
                buttonY_->execute();
            else if (isPressed(BUTTON_A))
                buttonA_->execute();
            else if (isPressed(BUTTON_B))
                buttonB_->execute();
        }
        //^handle-input-commands
    }

    namespace CommandedActors
    {
        class GameActor
        {
        public:
            void jump()
            {
            }
        };

        //^actor-command
        class Command
        {
        public:
            virtual ~Command()
            {
            }
            virtual void execute(GameActor& actor) = 0;
        };
        //^actor-command

        //^jump-actor
        class JumpCommand : public Command
        {
        public:
            virtual void execute(GameActor& actor)
            {
                actor.jump();
            }
        };
        //^jump-actor

        class InputHandler
        {
        public:
            Command* handleInput();

        private:
            Command* buttonX_;
            Command* buttonY_;
            Command* buttonA_;
            Command* buttonB_;
        };

        //^handle-input-return
        Command* InputHandler::handleInput()
        {
            if (isPressed(BUTTON_X))
                return buttonX_;
            if (isPressed(BUTTON_Y))
                return buttonY_;
            if (isPressed(BUTTON_A))
                return buttonA_;
            if (isPressed(BUTTON_B))
                return buttonB_;

            // Nothing pressed, so do nothing.
            return NULL;
        }
        //^handle-input-return

        void executeCommand()
        {
            InputHandler inputHandler;
            GameActor actor;
            //^call-actor-command
            Command* command = inputHandler.handleInput();
            if (command)
            {
                command->execute(actor);
            }
            //^call-actor-command
            use(actor);
        }
    }

    namespace Undo
    {
        class Unit
        {
        public:
            int x()
            {
                return 0;
            }
            int y()
            {
                return 0;
            }

            void moveTo([[maybe_unused]] int x, [[maybe_unused]] int y)
            {
            }
        };

        namespace UndoBefore
        {
            class Command
            {
            public:
                virtual ~Command()
                {
                }
                virtual void execute() = 0;
            };

            //^move-unit
            class MoveUnitCommand : public Command
            {
            public:
                MoveUnitCommand(Unit* unit, int x, int y)
                    : unit_(unit),
                      x_(x),
                      y_(y)
                {
                }

                virtual void execute()
                {
                    unit_->moveTo(x_, y_);
                }

            private:
                Unit* unit_;
                int x_, y_;
            };
            //^move-unit

            Unit* getSelectedUnit()
            {
                return NULL;
            }

            //^get-move
            Command* handleInput()
            {
                Unit* unit = getSelectedUnit();

                if (isPressed(BUTTON_UP))
                {
                    // Move the unit up one.
                    int destY = unit->y() - 1;
                    return new MoveUnitCommand(unit, unit->x(), destY);
                }

                if (isPressed(BUTTON_DOWN))
                {
                    // Move the unit down one.
                    int destY = unit->y() + 1;
                    return new MoveUnitCommand(unit, unit->x(), destY);
                }

                // Other moves...

                return NULL;
            }
            //^get-move
        }

        namespace UndoAfter
        {
            //^undo-command
            class Command
            {
            public:
                virtual ~Command()
                {
                }
                virtual void execute() = 0;
                virtual void undo() = 0;
            };
            //^undo-command

            //^undo-move-unit
            class MoveUnitCommand : public Command
            {
            public:
                MoveUnitCommand(Unit* unit, int x, int y)
                    : unit_(unit),
                      xBefore_(0),
                      yBefore_(0),
                      x_(x),
                      y_(y)
                {
                }

                virtual void execute()
                {
                    // Remember the unit's position before the move
                    // so we can restore it.
                    // ���ƶ�֮ǰ��ס��λ��λ�ã��Ա����ǿ��Խ���ָ���
                    xBefore_ = unit_->x();
                    yBefore_ = unit_->y();

                    unit_->moveTo(x_, y_);
                }

                virtual void undo()
                {
                    unit_->moveTo(xBefore_, yBefore_);
                }

            private:
                Unit* unit_;
                int xBefore_, yBefore_;
                int x_, y_;
            };
            //^undo-move-unit
        }
    }
}

#endif
