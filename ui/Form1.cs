using static System.Windows.Forms.VisualStyles.VisualStyleElement.Window;

namespace FluteFingers.UI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void openFileDialog1_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            // TODO idiomatic cast & syntax?
            OpenFileDialog dialog = (OpenFileDialog)sender;
            // TODO why am I never allowed to constify things here?
            // were this even idiomatic c#? is this even necessary due to
            // properties...? ah nvm. I'll read all about it...
            Core.Document document = this.ReadDocument(dialog.FileName);
            string message = string.Format(
                "This document has {0} bars and {1} systems",
                document.Bars, document.Systems);
            this.toolStripStatusLabel1.Text = message;
        }

        private Core.Document ReadDocument(string path)
        {
            switch (System.IO.Path.GetExtension(path))
            {
                case ".capx":
                    // TODO fix build system: this dynamic invocation fails if
                    // ui.exe is not next to core(-clrbridge).dll
                    return FluteFingers.Core.Document.FromCapXML10(path);
                case ".musicxml":
                    return FluteFingers.Core.Document.FromMusicXML(path);
            }
            throw new Exception("unreachable, extension must be known");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.openFileDialog.ShowDialog();
        }
    }
}
