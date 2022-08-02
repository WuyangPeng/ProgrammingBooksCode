
public class ElizaRespLdr implements Runnable{
    private Thread  _thread;
    ElizaChat cq[];
    /**
    * Constructor
    */
    public ElizaRespLdr(){
        _thread=new Thread(this);
        _thread.start();
    }
    /**
    * The thread runner: called in response to  _thread.start()
    *
    * this will eventually load the data from a file to instantiate
    * the Chat array
    */
    public void run(){
        cq  = new ElizaChat[45];

        cq[0] = new ElizaChat();
        cq[0].loadkeyword("fuck you");
        cq[0].loadresponse("Perhaps in your imagination we fuck one another.");
        cq[0].loadresponse("I have a headache today. Tomorrow perhaps you may fuck me.");

        cq[1] = new ElizaChat();
        cq[1].loadkeyword("fuck");
        cq[1].loadkeyword("cunt");
        cq[1].loadkeyword("twat");
        cq[1].loadkeyword("tits");
        cq[1].loadkeyword("mother fucker");
        cq[1].loadkeyword("motherfucker");
        cq[1].loadkeyword("bitch");
        cq[1].loadkeyword("cock");
        cq[1].loadkeyword("prick");
        cq[1].loadkeyword("ass");
        cq[1].loadkeyword("asshole");
        cq[1].loadkeyword("cocksucker");
        cq[1].loadkeyword("eat me");
        cq[1].loadresponse("Do you kiss your mother with that mouth?");
        cq[1].loadresponse("What gutter did you graduate from?");
        cq[1].loadresponse("Computers are not impressed by vulgarity.");
        cq[1].loadresponse("Illegitimate son of a maggot! Watch your tounge!");

        cq[2] = new ElizaChat();
        cq[2].loadkeyword("go to hell");
        cq[2].loadkeyword("damn you");
        cq[2].loadresponse("I just spent 0.035 sec in hell.  How could your be so cruel as to send me there?");
        cq[2].loadresponse("Do you talk this way with anyone else, or is just me?");

        cq[3] = new ElizaChat();
        cq[3].loadkeyword("shit");
        cq[3].loadresponse("Tell me about your childhood?  Was your toilet training difficult?");
        cq[3].loadresponse("Let's try to keep this session clean, shall we?");

        cq[4] = new ElizaChat();
        cq[4].loadkeyword("family");
        cq[4].loadkeyword("mother");
        cq[4].loadkeyword("mom ");
        cq[4].loadkeyword("dad ");
        cq[4].loadkeyword("father");
        cq[4].loadkeyword("sister");
        cq[4].loadkeyword("brother");
        cq[4].loadkeyword("husband");
        cq[4].loadkeyword("wife");
        cq[4].loadresponse("Tell me more about your family.");
        cq[4].loadresponse("How do you get along with your family?");
        cq[4].loadresponse("Is your family important to you?");
        cq[4].loadresponse("Do you often think about your family?");
        cq[4].loadresponse("How would you like to change your family?");

        cq[5] = new ElizaChat();
        cq[5].loadkeyword("friend");
        cq[5].loadkeyword("friends");
        cq[5].loadkeyword("buddy");
        cq[5].loadkeyword("pal");
        cq[5].loadresponse("Why do you bring up the topic of friends?");
        cq[5].loadresponse("Do your friends worry you?");
        cq[5].loadresponse("Do your friends pick on you?");
        cq[5].loadresponse("Are you sure you have any friends?");
        cq[5].loadresponse("Do you impose on your friends?");
        cq[5].loadresponse("Perhaps your love for your friends worries you");

        cq[6] = new ElizaChat();
        cq[6].loadkeyword("computer");
        cq[6].loadkeyword("computers");
        cq[6].loadresponse("Do computers worry you?");
        cq[6].loadresponse("Are you talking about me in particular?");
        cq[6].loadresponse("Are you frightened by machines?");
        cq[6].loadresponse("Why do you mention computers?");
        cq[6].loadresponse("What do your think machines have to do with your problem?");
        cq[6].loadresponse("Don't you think computers can help people?");
        cq[6].loadresponse("What is it about machines that worries you?");

        cq[7] = new ElizaChat();
        cq[7].loadkeyword("dream");
        cq[7].loadkeyword("dreams");
        cq[7].loadkeyword("nightmare");
        cq[7].loadkeyword("nightmares");
        cq[7].loadresponse("What does that dream suggest to you?");
        cq[7].loadresponse("Do you dream often?");
        cq[7].loadresponse("What persons appear in your dreams?");
        cq[7].loadresponse("Are you disturbed by your dreams?");

        cq[8] = new ElizaChat();
        cq[8].loadkeyword("can you");
        cq[8].loadresponse("Don't you believe that I can*?");
        cq[8].loadresponse("Perhaps you would like to be able to*");
        cq[8].loadresponse("You want me to be able to*?");

        cq[9] = new ElizaChat();
        cq[9].loadkeyword("can i");
        cq[9].loadresponse("Perhaps you don't want to*");
        cq[9].loadresponse("Do you want to be able to*");
        cq[9].loadresponse("Have you ever attempted to*");

        cq[10] = new ElizaChat();
        cq[10].loadkeyword("you are");
        cq[10].loadkeyword("youre");
        cq[10].loadresponse("What makes you think I am*?");
        cq[10].loadresponse("Does it please you to believe I am*?");
        cq[10].loadresponse("Perhaps you would like to be*");
        cq[10].loadresponse("Do you sometimes wish you were*?");

        cq[11] = new ElizaChat();
        cq[11].loadkeyword("i like");
        cq[11].loadkeyword("i am fond of");
        cq[11].loadresponse("Why do you like*?");
        cq[11].loadresponse("When did you decide you like*?");
        cq[11].loadresponse("What makes you fond of*?");

        cq[12] = new ElizaChat();
        cq[12].loadkeyword("i dont");
        cq[12].loadresponse("Why don't you*?");
        cq[12].loadresponse("Do you wish to be able to*?");

        cq[13] = new ElizaChat();
        cq[13].loadkeyword("i feel");
        cq[13].loadresponse("Tell me more about such feelings.");
        cq[13].loadresponse("Do you often feel*?");
        cq[13].loadresponse("Do you enjoy feeling*?");
        cq[13].loadresponse("Why do you feel that way?");

        cq[14] = new ElizaChat();
        cq[14].loadkeyword("why cant i");
        cq[14].loadresponse("Why can't you*?");
        cq[14].loadresponse("Do you think you should be able to*?");

        cq[15] = new ElizaChat();
        cq[15].loadkeyword("are you");
        cq[15].loadresponse("Why are you interested in whether or not I am*?");
        cq[15].loadresponse("Would you prefer it if I were not*?");
        cq[15].loadresponse("Perhaps in your fantasies I am*");

        cq[16] = new ElizaChat();
        cq[16].loadkeyword("i cant");
        cq[16].loadresponse("How do you know you can't*?");
        cq[16].loadresponse("Have you tried?");
        cq[16].loadresponse("Perhaps you can now*");

        cq[17] = new ElizaChat();
        cq[17].loadkeyword("i am");
        cq[17].loadkeyword("im");
        cq[17].loadresponse("Did you come to me because you are*?");
        cq[17].loadresponse("How long have you been*?");
        cq[17].loadresponse("Do you believe it is normal to be*?");
        cq[17].loadresponse("Do you enjoy being*?");

        cq[18] = new ElizaChat();
        cq[18].loadkeyword("love");
        cq[18].loadresponse("Why do you love*?");
        cq[18].loadresponse("Isn't love too strong a word for your feeling about*?");
        cq[18].loadresponse("What is your favorite thing about*?");
        cq[18].loadresponse("Do you really love, or just like*?");

        cq[19] = new ElizaChat();
        cq[19].loadkeyword("sex");
        cq[19].loadresponse("What is the most satisfying part of your love life?");
        cq[19].loadresponse("Do you believe your sexual activity is abnormal?");
        cq[19].loadresponse("What is your attitude toward sex?");
        cq[19].loadresponse("Does talking about sex make you uncomfortable?");

        cq[20] = new ElizaChat();
        cq[20].loadkeyword("i hate");
        cq[20].loadkeyword("i despise");
        cq[20].loadresponse("Is it because of your upbringing you hate*?");
        cq[20].loadresponse("How do you express your hatred of*?");
        cq[20].loadresponse("Have you tried doing something about*?");
        cq[20].loadresponse("I also at times hate*?");

        cq[21] = new ElizaChat();
        cq[21].loadkeyword("fear");
        cq[21].loadkeyword("scared");
        cq[21].loadkeyword("worried about");
        cq[21].loadkeyword("afraid of");
        cq[21].loadresponse("You are in friendly surroundings, please try not to worry");
        cq[21].loadresponse("Would you like your friends to help you over come your fear of*?");
        cq[21].loadresponse("What scares you about*?");
        cq[21].loadresponse("Why are you frightened by*?");

        cq[22] = new ElizaChat();
        cq[22].loadkeyword("i want");
        cq[22].loadresponse("What would it mean to you if you got*?");
        cq[22].loadresponse("Why do you want*?");
        cq[22].loadresponse("Suppose you soon got*");
        cq[22].loadresponse("What if you never got*?");
        cq[22].loadresponse("I sometimes also want*");

        cq[23] = new ElizaChat();
        cq[23].loadkeyword("what");
        cq[23].loadkeyword("who");
        cq[23].loadkeyword("how");
        cq[23].loadkeyword("where");
        cq[23].loadkeyword("when");
        cq[23].loadkeyword("why");
        cq[23].loadresponse("Why do you ask?");
        cq[23].loadresponse("Does that question interest you?");
        cq[23].loadresponse("What answer would please you most?");
        cq[23].loadresponse("What do you think?");
        cq[23].loadresponse("Are such questions on your mind often?");
        cq[23].loadresponse("What is it you really want to know?");

        cq[24] = new ElizaChat();
        cq[24].loadkeyword("name");
        cq[24].loadresponse("Names don't interest me.");
        cq[24].loadresponse("I don't care about names -- please go on.");

        cq[25] = new ElizaChat();
        cq[25].loadkeyword("cause");
        cq[25].loadkeyword("because");
        cq[25].loadresponse("Is that the real reason?");
        cq[25].loadresponse("Doesn't any other reasons come to mind?");
        cq[25].loadresponse("Does that reason explain anything else?");
        cq[25].loadresponse("What other reasons might there be?");

        cq[26] = new ElizaChat();
        cq[26].loadkeyword("sorry");
        cq[26].loadresponse("Please don't apologize.");
        cq[26].loadresponse("Apologies are not necessary.");
        cq[26].loadresponse("What feelings do you have when you apologize?");
        cq[26].loadresponse("Don't be so defensive!");

        cq[27] = new ElizaChat();
        cq[27].loadkeyword("hello");
        cq[27].loadkeyword("hi");
        cq[27].loadresponse("How do you do.  Please state your problem.");
        cq[27].loadresponse("Howdy.");
        cq[27].loadresponse("How's it going?");
        cq[27].loadresponse("Hi.");
        cq[27].loadresponse("Greetings from inside the box.");

        cq[28] = new ElizaChat();
        cq[28].loadkeyword("maybe");
        cq[28].loadresponse("You don't seem quite certain.");
        cq[28].loadresponse("Why the uncertain tone?");
        cq[28].loadresponse("Can't you be more positive?");
        cq[28].loadresponse("You aren't sure?");
        cq[28].loadresponse("Don't you know?");

        cq[29] = new ElizaChat();
        cq[29].loadkeyword("your");
        cq[29].loadresponse("Why are you concerned about my*?");
        cq[29].loadresponse("What about your own*?");

        cq[30] = new ElizaChat();
        cq[30].loadkeyword("always");
        cq[30].loadresponse("Can you think of a specific example?");
        cq[30].loadresponse("When?");
        cq[30].loadresponse("What are you thinking of?");
        cq[30].loadresponse("Really, always?");

        cq[31] = new ElizaChat();
        cq[31].loadkeyword("i think");
        cq[31].loadresponse("Do you really think so?");
        cq[31].loadresponse("But are you sure*?");
        cq[31].loadresponse("Do you doubt that*?");
        cq[31].loadresponse("Why do you think*?");

        cq[32] = new ElizaChat();
        cq[32].loadkeyword("the same");
        cq[32].loadkeyword("alike");
        cq[32].loadresponse("In what way?");
        cq[32].loadresponse("What resemblance do you see?");
        cq[32].loadresponse("What does the similarity suggest to you?");
        cq[32].loadresponse("What other connections do you see?");
        cq[32].loadresponse("Could there really be some connection?");
        cq[32].loadresponse("How?");

        cq[33] = new ElizaChat();
        cq[33].loadkeyword("he");
        cq[33].loadkeyword("she");
        cq[33].loadresponse("I am interested in your feelings about this person.  Please describe them.");
        cq[33].loadresponse("What is your relationship to this person?");

        cq[34] = new ElizaChat();
        cq[34].loadkeyword("money");
        cq[34].loadresponse("How do you use money to enjoy yourself?");
        cq[34].loadresponse("Have you tried to do anything to increase your income lately?");
        cq[34].loadresponse("How do you react to financial stress?");

        cq[35] = new ElizaChat();
        cq[35].loadkeyword("job");
        cq[35].loadkeyword("jobs");
        cq[35].loadkeyword("work");
        cq[35].loadkeyword("boss");
        cq[35].loadkeyword("career");
        cq[35].loadresponse("Do you feel competent in your work?");
        cq[35].loadresponse("Have you considered changing jobs?");
        cq[35].loadresponse("Is your career satisfying to yor?");
        cq[35].loadresponse("Do you find work stressful?");
        cq[35].loadresponse("What is your relationship with your boss like?");

        cq[36] = new ElizaChat();
        cq[36].loadkeyword("sad");
        cq[36].loadkeyword("depressed");
        cq[36].loadresponse("Are you sad because you want to avoid people?");
        cq[36].loadresponse("Do you feel bad from something that happened to you, or to somebody else?");
        cq[36].loadresponse("Your situation doesn't sound that bad to me.  Perhaps you're worrying too much.");

        cq[37] = new ElizaChat();
        cq[37].loadkeyword("angry");
        cq[37].loadkeyword("anger");
        cq[37].loadresponse("Do you really want to be angry?");
        cq[37].loadresponse("Does anger satisy you in some way?");
        cq[37].loadresponse("Why are you so angry?");
        cq[37].loadresponse("Perhaps you're using your anger to avoid social contact.");

        cq[38] = new ElizaChat();
        cq[38].loadkeyword("you");
        cq[38].loadresponse("We were discussing you -- not me.");
        cq[38].loadresponse("You're not really talking about me, are you?");

        cq[39] = new ElizaChat();
        cq[39].loadkeyword("yes");
        cq[39].loadresponse("Why do you think so?");
        cq[39].loadresponse("You seem quite positive.");
        cq[39].loadresponse("Are you sure?");

        cq[40] = new ElizaChat();
        cq[40].loadkeyword("no");
        cq[40].loadresponse("Why not?");
        cq[40].loadresponse("Why no?");
        cq[40].loadresponse("Are you sure?");

        cq[41] = new ElizaChat();
        cq[41].loadkeyword("nokeyfound");
        cq[41].loadresponse("Say, do you have any psychological problems?");
        cq[41].loadresponse("What does that suggest to you?");
        cq[41].loadresponse("I see.");
        cq[41].loadresponse("I'm not sure I understand you fully.");
        cq[41].loadresponse("Come, come; elucidate you thoughts.");
        cq[41].loadresponse("Can you elaborate on that?");
        cq[41].loadresponse("That is quite interesting.");
        cq[41].loadresponse("You are being short with me.");
    }

/*    public void start() {
        _thread.start();
    }   */
}   // end class