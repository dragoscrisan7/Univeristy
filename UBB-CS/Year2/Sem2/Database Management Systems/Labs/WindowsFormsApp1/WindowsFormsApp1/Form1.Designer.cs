namespace WindowsFormsApp1
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
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.Connect_Button = new System.Windows.Forms.Button();
            this.Insert_Button = new System.Windows.Forms.Button();
            this.Delete_Button = new System.Windows.Forms.Button();
            this.Update_Button = new System.Windows.Forms.Button();
            this.Generate_Textboxes_Button = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.insert_sub = new System.Windows.Forms.Button();
            this.delete_sub = new System.Windows.Forms.Button();
            this.update_sub = new System.Windows.Forms.Button();
            this.generate_textboxes_sub = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(12, 79);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.Size = new System.Drawing.Size(368, 229);
            this.dataGridView1.TabIndex = 0;
            this.dataGridView1.RowHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGridView1_RowHeaderMouseClick);
            // 
            // Connect_Button
            // 
            this.Connect_Button.Location = new System.Drawing.Point(104, 12);
            this.Connect_Button.Name = "Connect_Button";
            this.Connect_Button.Size = new System.Drawing.Size(109, 44);
            this.Connect_Button.TabIndex = 1;
            this.Connect_Button.Text = "Connect";
            this.Connect_Button.UseVisualStyleBackColor = true;
            this.Connect_Button.Click += new System.EventHandler(this.Connect_Button_Click);
            // 
            // Insert_Button
            // 
            this.Insert_Button.Location = new System.Drawing.Point(399, 79);
            this.Insert_Button.Name = "Insert_Button";
            this.Insert_Button.Size = new System.Drawing.Size(109, 44);
            this.Insert_Button.TabIndex = 2;
            this.Insert_Button.Text = "Insert";
            this.Insert_Button.UseVisualStyleBackColor = true;
            this.Insert_Button.Click += new System.EventHandler(this.Insert_Button_Click);
            // 
            // Delete_Button
            // 
            this.Delete_Button.Location = new System.Drawing.Point(399, 140);
            this.Delete_Button.Name = "Delete_Button";
            this.Delete_Button.Size = new System.Drawing.Size(109, 44);
            this.Delete_Button.TabIndex = 3;
            this.Delete_Button.Text = "Delete";
            this.Delete_Button.UseVisualStyleBackColor = true;
            this.Delete_Button.Click += new System.EventHandler(this.Delete_Button_Click);
            // 
            // Update_Button
            // 
            this.Update_Button.Location = new System.Drawing.Point(399, 202);
            this.Update_Button.Name = "Update_Button";
            this.Update_Button.Size = new System.Drawing.Size(109, 44);
            this.Update_Button.TabIndex = 4;
            this.Update_Button.Text = "Update";
            this.Update_Button.UseVisualStyleBackColor = true;
            this.Update_Button.Click += new System.EventHandler(this.Update_Button_Click);
            // 
            // Generate_Textboxes_Button
            // 
            this.Generate_Textboxes_Button.Location = new System.Drawing.Point(399, 264);
            this.Generate_Textboxes_Button.Name = "Generate_Textboxes_Button";
            this.Generate_Textboxes_Button.Size = new System.Drawing.Size(109, 44);
            this.Generate_Textboxes_Button.TabIndex = 5;
            this.Generate_Textboxes_Button.Text = "Generate Textboxes";
            this.Generate_Textboxes_Button.UseVisualStyleBackColor = true;
            this.Generate_Textboxes_Button.Click += new System.EventHandler(this.Generate_Textboxes_Button_Click);
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(535, 79);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(157, 229);
            this.panel1.TabIndex = 6;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            // 
            // dataGridView2
            // 
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(12, 328);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.Size = new System.Drawing.Size(496, 229);
            this.dataGridView2.TabIndex = 7;
            this.dataGridView2.RowHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.subDataGrid_RowHeaderMouseClick);
            // 
            // insert_sub
            // 
            this.insert_sub.Location = new System.Drawing.Point(535, 328);
            this.insert_sub.Name = "insert_sub";
            this.insert_sub.Size = new System.Drawing.Size(109, 44);
            this.insert_sub.TabIndex = 8;
            this.insert_sub.Text = "Insert";
            this.insert_sub.UseVisualStyleBackColor = true;
            this.insert_sub.Click += new System.EventHandler(this.insert_sub_Click);
            // 
            // delete_sub
            // 
            this.delete_sub.Location = new System.Drawing.Point(535, 378);
            this.delete_sub.Name = "delete_sub";
            this.delete_sub.Size = new System.Drawing.Size(109, 44);
            this.delete_sub.TabIndex = 9;
            this.delete_sub.Text = "Delete";
            this.delete_sub.UseVisualStyleBackColor = true;
            this.delete_sub.Click += new System.EventHandler(this.delete_sub_Click);
            // 
            // update_sub
            // 
            this.update_sub.Location = new System.Drawing.Point(535, 428);
            this.update_sub.Name = "update_sub";
            this.update_sub.Size = new System.Drawing.Size(109, 44);
            this.update_sub.TabIndex = 10;
            this.update_sub.Text = "Update";
            this.update_sub.UseVisualStyleBackColor = true;
            this.update_sub.Click += new System.EventHandler(this.update_sub_Click);
            // 
            // generate_textboxes_sub
            // 
            this.generate_textboxes_sub.Location = new System.Drawing.Point(535, 478);
            this.generate_textboxes_sub.Name = "generate_textboxes_sub";
            this.generate_textboxes_sub.Size = new System.Drawing.Size(109, 44);
            this.generate_textboxes_sub.TabIndex = 11;
            this.generate_textboxes_sub.Text = "Generate Textboxes";
            this.generate_textboxes_sub.UseVisualStyleBackColor = true;
            this.generate_textboxes_sub.Click += new System.EventHandler(this.generate_textboxes_sub_Click);
            // 
            // panel2
            // 
            this.panel2.Location = new System.Drawing.Point(665, 314);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(157, 229);
            this.panel2.TabIndex = 12;
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(882, 554);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.generate_textboxes_sub);
            this.Controls.Add(this.update_sub);
            this.Controls.Add(this.delete_sub);
            this.Controls.Add(this.insert_sub);
            this.Controls.Add(this.dataGridView2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.Generate_Textboxes_Button);
            this.Controls.Add(this.Update_Button);
            this.Controls.Add(this.Delete_Button);
            this.Controls.Add(this.Insert_Button);
            this.Controls.Add(this.Connect_Button);
            this.Controls.Add(this.dataGridView1);
            this.Name = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button Connect_Button;
        private System.Windows.Forms.Button Insert_Button;
        private System.Windows.Forms.Button Delete_Button;
        private System.Windows.Forms.Button Update_Button;
        private System.Windows.Forms.Button Generate_Textboxes_Button;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.Button insert_sub;
        private System.Windows.Forms.Button delete_sub;
        private System.Windows.Forms.Button update_sub;
        private System.Windows.Forms.Button generate_textboxes_sub;
        private System.Windows.Forms.Panel panel2;
    }
}

