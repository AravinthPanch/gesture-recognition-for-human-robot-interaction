namespace GesturesRecognition
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose( bool disposing )
        {
            if ( disposing && ( components != null ) )
            {
                components.Dispose( );
            }
            base.Dispose( disposing );
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent( )
        {
            this.components = new System.ComponentModel.Container( );
            this.mainMenu = new System.Windows.Forms.MenuStrip( );
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem( );
            this.openLocalcameraToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem( );
            this.openvideoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem( );
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator( );
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem( );
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem( );
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem( );
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog( );
            this.statusBar = new System.Windows.Forms.StatusStrip( );
            this.fpsLabel = new System.Windows.Forms.ToolStripStatusLabel( );
            this.mainPanel = new System.Windows.Forms.Panel( );
            this.cameraWindow = new GesturesRecognition.CameraWindow( );
            this.timer = new System.Windows.Forms.Timer( this.components );
            this.mainMenu.SuspendLayout( );
            this.statusBar.SuspendLayout( );
            this.mainPanel.SuspendLayout( );
            this.SuspendLayout( );
            // 
            // mainMenu
            // 
            this.mainMenu.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.helpToolStripMenuItem} );
            this.mainMenu.Location = new System.Drawing.Point( 0, 0 );
            this.mainMenu.Name = "mainMenu";
            this.mainMenu.Size = new System.Drawing.Size( 434, 24 );
            this.mainMenu.TabIndex = 0;
            this.mainMenu.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.openLocalcameraToolStripMenuItem,
            this.openvideoToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem} );
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size( 37, 20 );
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // openLocalcameraToolStripMenuItem
            // 
            this.openLocalcameraToolStripMenuItem.Name = "openLocalcameraToolStripMenuItem";
            this.openLocalcameraToolStripMenuItem.ShortcutKeys = ( (System.Windows.Forms.Keys) ( ( System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C ) ) );
            this.openLocalcameraToolStripMenuItem.Size = new System.Drawing.Size( 215, 22 );
            this.openLocalcameraToolStripMenuItem.Text = "Open local &camera";
            this.openLocalcameraToolStripMenuItem.Click += new System.EventHandler( this.openLocalcameraToolStripMenuItem_Click );
            // 
            // openvideoToolStripMenuItem
            // 
            this.openvideoToolStripMenuItem.Name = "openvideoToolStripMenuItem";
            this.openvideoToolStripMenuItem.ShortcutKeys = ( (System.Windows.Forms.Keys) ( ( System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V ) ) );
            this.openvideoToolStripMenuItem.Size = new System.Drawing.Size( 215, 22 );
            this.openvideoToolStripMenuItem.Text = "Open &video";
            this.openvideoToolStripMenuItem.Click += new System.EventHandler( this.openvideoToolStripMenuItem_Click );
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size( 212, 6 );
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size( 215, 22 );
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler( this.exitToolStripMenuItem_Click );
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem} );
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size( 44, 20 );
            this.helpToolStripMenuItem.Text = "&Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size( 107, 22 );
            this.aboutToolStripMenuItem.Text = "&About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler( this.aboutToolStripMenuItem_Click );
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "AVI files (*.avi)|*.avi|All files (*.*)|*.*";
            this.openFileDialog.Title = "Opem video";
            // 
            // statusBar
            // 
            this.statusBar.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.fpsLabel} );
            this.statusBar.Location = new System.Drawing.Point( 0, 332 );
            this.statusBar.Name = "statusBar";
            this.statusBar.Size = new System.Drawing.Size( 434, 22 );
            this.statusBar.TabIndex = 1;
            // 
            // fpsLabel
            // 
            this.fpsLabel.BorderSides = ( (System.Windows.Forms.ToolStripStatusLabelBorderSides) ( ( ( ( System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top )
                        | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right )
                        | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom ) ) );
            this.fpsLabel.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner;
            this.fpsLabel.Name = "fpsLabel";
            this.fpsLabel.Size = new System.Drawing.Size( 419, 17 );
            this.fpsLabel.Spring = true;
            this.fpsLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // mainPanel
            // 
            this.mainPanel.Controls.Add( this.cameraWindow );
            this.mainPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainPanel.Location = new System.Drawing.Point( 0, 24 );
            this.mainPanel.Name = "mainPanel";
            this.mainPanel.Size = new System.Drawing.Size( 434, 308 );
            this.mainPanel.TabIndex = 2;
            // 
            // cameraWindow
            // 
            this.cameraWindow.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.cameraWindow.Camera = null;
            this.cameraWindow.Location = new System.Drawing.Point( 57, 34 );
            this.cameraWindow.Name = "cameraWindow";
            this.cameraWindow.Size = new System.Drawing.Size( 320, 240 );
            this.cameraWindow.TabIndex = 0;
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler( this.timer_Tick );
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size( 434, 354 );
            this.Controls.Add( this.mainPanel );
            this.Controls.Add( this.statusBar );
            this.Controls.Add( this.mainMenu );
            this.MainMenuStrip = this.mainMenu;
            this.Name = "MainForm";
            this.Text = "Gestures Recognition";
            this.SizeChanged += new System.EventHandler( this.MainForm_SizeChanged );
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler( this.MainForm_FormClosing );
            this.mainMenu.ResumeLayout( false );
            this.mainMenu.PerformLayout( );
            this.statusBar.ResumeLayout( false );
            this.statusBar.PerformLayout( );
            this.mainPanel.ResumeLayout( false );
            this.ResumeLayout( false );
            this.PerformLayout( );

        }

        #endregion

        private System.Windows.Forms.MenuStrip mainMenu;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openLocalcameraToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openvideoToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.StatusStrip statusBar;
        private System.Windows.Forms.ToolStripStatusLabel fpsLabel;
        private System.Windows.Forms.Panel mainPanel;
        private System.Windows.Forms.Timer timer;
        private CameraWindow cameraWindow;
    }
}

