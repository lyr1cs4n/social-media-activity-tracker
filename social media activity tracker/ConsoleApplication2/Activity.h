#pragma once
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
enum  ReactionType {
    LIKE,
    LAUGH,
    SADFACE
};
class Activity
{
public:

    struct Post {
        string content;

        Post(const string& text) : content(text) {}
    };

    struct Comment {
        string username;
        string targetUser;
        string targetPost;
        string comment;

        Comment(const string& user, const string& targetUser, const string& text, const string& targetPost)
            : username(user), targetUser(targetUser), comment(text), targetPost(targetPost){}
    };

    struct Reaction {

        string username;
        string targetUser;
        string targetPost;
        ReactionType reactionType;

        Reaction(const string& user, const string& targetUser, ReactionType type, const string& targetPost)
            : username(user), targetUser(targetUser), reactionType(type), targetPost(targetPost){}
    };

    struct Follow {
        string followerUsername;
        string followingUsername;

        Follow(const string& follower, const string& following)
            : followerUsername(follower), followingUsername(following) {}
    };

    struct ActivityData {
        enum Type { POST, COMMENT, REACTION, FOLLOW };

        Type type;
        union {
            Post post;
            Comment comment;
            Reaction reaction;
            Follow follow;
        };

        ActivityData(){}

        ActivityData(const ActivityData& other) : type(other.type) {
            switch (type) {
            case POST:
                new (&post) Post(other.post);
                break;
            case COMMENT:
                new (&comment) Comment(other.comment);
                break;
            case REACTION:
                new (&reaction) Reaction(other.reaction);
                break;
            case FOLLOW:
                new (&follow) Follow(other.follow);
                break;
            }
        }

        ActivityData(const Post& p) : type(POST), post(p) {}

        ActivityData(const Comment& c) : type(COMMENT), comment(c) {}

        ActivityData(const Reaction& r) : type(REACTION), reaction(r) {}

        ActivityData(const Follow& f) : type(FOLLOW), follow(f) {}

        ~ActivityData() {
            switch (type) {
            case POST:
                post.~Post();
                break;
            case COMMENT:
                comment.~Comment();
                break;
            case REACTION:
                reaction.~Reaction();
                break;
            case FOLLOW:
                follow.~Follow();
                break;
            }
        }
        bool operator==(const ActivityData& other) const {
            if (type != other.type) {
                return false;
            }

            switch (type) {
            case POST:
                return post.content == other.post.content;
            case COMMENT:
                return comment.username == other.comment.username &&
                    comment.targetUser == other.comment.targetUser &&
                    comment.comment == other.comment.comment;
            case REACTION:
                return reaction.username == other.reaction.username &&
                    reaction.targetUser == other.reaction.targetUser &&
                    reaction.targetPost == other.reaction.targetPost &&
                    reaction.reactionType == other.reaction.reactionType;
            case FOLLOW:
                return follow.followerUsername == other.follow.followerUsername &&
                    follow.followingUsername == other.follow.followingUsername;
            default:
                return false;
            }
        }
        friend ostream& operator<<(ostream& os, const ActivityData& activityData) {
            switch (activityData.type) {
            case POST:
                os <<  "    Post : " << activityData.post.content << endl;
                break;
            case COMMENT:
                os <<"    " << " commented: \"" << activityData.comment.comment << "\" on " << activityData.comment.targetUser << "'s post: " << activityData.comment.targetPost << endl;
                break;
            case REACTION:
                os << "    " << activityData.reaction.username << " ";

                switch (activityData.reaction.reactionType) {
                case ReactionType::LIKE:
                    os << "liked";
                    break;
                case ReactionType::LAUGH:
                    os << "laughed";
                    break;
                case ReactionType::SADFACE:
                    os << "reacted with a sad face";
                    break;
                default:
                    os << "reacted";
                    break;
                }

                cout << " on " << activityData.reaction.targetUser << "'s post: " << activityData.reaction.targetPost << endl;
                break;
            case FOLLOW:
                os << "    " << activityData.follow.followerUsername << " Followed " << activityData.follow.followingUsername << endl;
                break;
            default:
                os << "    Invalid Activity Type";
            }
            return os;
        }
    };

    ActivityData createPost(const string& currentUser) {
        string postContent;
        cout << "[*] "
            << "\033[33mEnter Post Content: \033[0m" ;
        std::getline(std::cin, postContent);
        Post post(postContent);
        return ActivityData(post);
    }

    ActivityData createComment(const string& currentUser,  const string& targetUser, const string& targetPost) {
        string commentContent;
        cout << "[*] "
            << "\033[33mEnter Comment: \033[0m" ;
        std::getline(std::cin, commentContent);
        Comment comment(currentUser, targetUser, commentContent, targetPost);
        return ActivityData(comment);
    }

    ReactionType getReactionInput() {
        cout << "[*] "
            << "\033[33mEnter The Reaction [like, laugh, sadface]: \033[0m" ;
        string reactionInput;
        cin >> reactionInput;

        transform(reactionInput.begin(), reactionInput.end(), reactionInput.begin(), ::tolower);

        if (reactionInput == "like") {
            return ReactionType::LIKE;
        }
        else if (reactionInput == "laugh") {
            return ReactionType::LAUGH;
        }
        else if (reactionInput == "sadface") {
            return ReactionType::SADFACE;
        }
        else {
  
            cout << "    Invalid input. Defaulting to 'like'." << endl;
            return ReactionType::LIKE;
        }
    }

    ActivityData reactToPost(const string& currentUser, const string& targetUser, const string& targetPost) {
        ReactionType reactionType = getReactionInput();
        Reaction reaction(currentUser, targetUser, reactionType, targetPost);
        return ActivityData(reaction);
    }

    ActivityData followUser(const string& currentUser, const string& targetUser) {
        Follow follow(currentUser, targetUser);
        return ActivityData(follow);
    }
};

