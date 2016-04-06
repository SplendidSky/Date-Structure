
using System;

namespace Models
{
    public class Message
    {
        public string Name;
        public DateTime Published;
        public string Comment;
        public bool IsSelf;

        public Message(string Name, DateTime Published, string Comment, bool IsSelf)
        {
            this.Name = Name;
            this.Published = Published;
            this.Comment = Comment;
            this.IsSelf = IsSelf;
        }
    }
}
