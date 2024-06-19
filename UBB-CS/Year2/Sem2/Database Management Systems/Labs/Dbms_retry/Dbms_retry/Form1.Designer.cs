namespace Dbms_retry
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ClassDataGrid = new System.Windows.Forms.DataGridView();
            this.ClassLabel = new System.Windows.Forms.Label();
            this.UpdateButton = new System.Windows.Forms.Button();
            this.SubClassDataGrid = new System.Windows.Forms.DataGridView();
            this.SubClassLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.ClassDataGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SubClassDataGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // ClassDataGrid
            // 
            this.ClassDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ClassDataGrid.Location = new System.Drawing.Point(29, 71);
            this.ClassDataGrid.Name = "ClassDataGrid";
            this.ClassDataGrid.Size = new System.Drawing.Size(313, 209);
            this.ClassDataGrid.TabIndex = 0;
            this.ClassDataGrid.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.ClassDataGrid_CellContentClick);
            // 
            // ClassLabel
            // 
            this.ClassLabel.AutoSize = true;
            this.ClassLabel.Location = new System.Drawing.Point(26, 45);
            this.ClassLabel.Name = "ClassLabel";
            this.ClassLabel.Size = new System.Drawing.Size(51, 13);
            this.ClassLabel.TabIndex = 1;
            this.ClassLabel.Text = "Countries";
            // 
            // UpdateButton
            // 
            this.UpdateButton.Location = new System.Drawing.Point(320, 332);
            this.UpdateButton.Name = "UpdateButton";
            this.UpdateButton.Size = new System.Drawing.Size(75, 23);
            this.UpdateButton.TabIndex = 2;
            this.UpdateButton.Text = "Update";
            this.UpdateButton.UseVisualStyleBackColor = true;
            this.UpdateButton.Click += new System.EventHandler(this.UpdateButton_Click);
            // 
            // SubClassDataGrid
            // 
            this.SubClassDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.SubClassDataGrid.Location = new System.Drawing.Point(438, 71);
            this.SubClassDataGrid.Name = "SubClassDataGrid";
            this.SubClassDataGrid.Size = new System.Drawing.Size(296, 209);
            this.SubClassDataGrid.TabIndex = 3;
            // 
            // SubClassLabel
            // 
            this.SubClassLabel.AutoSize = true;
            this.SubClassLabel.Location = new System.Drawing.Point(435, 45);
            this.SubClassLabel.Name = "SubClassLabel";
            this.SubClassLabel.Size = new System.Drawing.Size(32, 13);
            this.SubClassLabel.TabIndex = 4;
            this.SubClassLabel.Text = "Cities";
            this.SubClassLabel.Click += new System.EventHandler(this.label2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.SubClassLabel);
            this.Controls.Add(this.SubClassDataGrid);
            this.Controls.Add(this.UpdateButton);
            this.Controls.Add(this.ClassLabel);
            this.Controls.Add(this.ClassDataGrid);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.ClassDataGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SubClassDataGrid)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView ClassDataGrid;
        private System.Windows.Forms.Label ClassLabel;
        private System.Windows.Forms.Button UpdateButton;
        private System.Windows.Forms.DataGridView SubClassDataGrid;
        private System.Windows.Forms.Label SubClassLabel;
    }
}

