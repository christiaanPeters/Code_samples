namespace decorator_pattern
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
            this.Laptop_listBox = new System.Windows.Forms.ListBox();
            this.group_laptops = new System.Windows.Forms.GroupBox();
            this.GamingLaptop_button = new System.Windows.Forms.Button();
            this.TravelLaptop_button = new System.Windows.Forms.Button();
            this.group_parts = new System.Windows.Forms.GroupBox();
            this.AddUSB_button = new System.Windows.Forms.Button();
            this.AddHDD_button = new System.Windows.Forms.Button();
            this.AddGPU_button = new System.Windows.Forms.Button();
            this.AddRAM_button = new System.Windows.Forms.Button();
            this.RemoveLaptop_button = new System.Windows.Forms.Button();
            this.PurchaseLaptop_button = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.Info_label = new System.Windows.Forms.Label();
            this.group_info_text = new System.Windows.Forms.GroupBox();
            this.listbox_purchase_info = new System.Windows.Forms.ListBox();
            this.group_laptops.SuspendLayout();
            this.group_parts.SuspendLayout();
            this.group_info_text.SuspendLayout();
            this.SuspendLayout();
            // 
            // Laptop_listBox
            // 
            this.Laptop_listBox.FormattingEnabled = true;
            this.Laptop_listBox.Location = new System.Drawing.Point(419, 12);
            this.Laptop_listBox.Name = "Laptop_listBox";
            this.Laptop_listBox.Size = new System.Drawing.Size(252, 394);
            this.Laptop_listBox.TabIndex = 0;
            this.Laptop_listBox.SelectedIndexChanged += new System.EventHandler(this.Laptop_listBox_SelectedIndexChanged);
            // 
            // group_laptops
            // 
            this.group_laptops.Controls.Add(this.GamingLaptop_button);
            this.group_laptops.Controls.Add(this.TravelLaptop_button);
            this.group_laptops.Location = new System.Drawing.Point(12, 12);
            this.group_laptops.Name = "group_laptops";
            this.group_laptops.Size = new System.Drawing.Size(354, 128);
            this.group_laptops.TabIndex = 1;
            this.group_laptops.TabStop = false;
            this.group_laptops.Text = "Laptops";
            // 
            // GamingLaptop_button
            // 
            this.GamingLaptop_button.Location = new System.Drawing.Point(200, 33);
            this.GamingLaptop_button.Name = "GamingLaptop_button";
            this.GamingLaptop_button.Size = new System.Drawing.Size(120, 65);
            this.GamingLaptop_button.TabIndex = 1;
            this.GamingLaptop_button.Text = "Gaming Laptop";
            this.GamingLaptop_button.UseVisualStyleBackColor = true;
            this.GamingLaptop_button.Click += new System.EventHandler(this.GamingLaptop_button_Click);
            // 
            // TravelLaptop_button
            // 
            this.TravelLaptop_button.Location = new System.Drawing.Point(30, 33);
            this.TravelLaptop_button.Name = "TravelLaptop_button";
            this.TravelLaptop_button.Size = new System.Drawing.Size(120, 65);
            this.TravelLaptop_button.TabIndex = 0;
            this.TravelLaptop_button.Text = "Travel Laptop";
            this.TravelLaptop_button.UseVisualStyleBackColor = true;
            this.TravelLaptop_button.Click += new System.EventHandler(this.TravelLaptop_button_Click);
            // 
            // group_parts
            // 
            this.group_parts.Controls.Add(this.AddUSB_button);
            this.group_parts.Controls.Add(this.AddHDD_button);
            this.group_parts.Controls.Add(this.AddGPU_button);
            this.group_parts.Controls.Add(this.AddRAM_button);
            this.group_parts.Enabled = false;
            this.group_parts.Location = new System.Drawing.Point(12, 162);
            this.group_parts.Name = "group_parts";
            this.group_parts.Size = new System.Drawing.Size(354, 266);
            this.group_parts.TabIndex = 2;
            this.group_parts.TabStop = false;
            this.group_parts.Text = "Parts";
            // 
            // AddUSB_button
            // 
            this.AddUSB_button.Location = new System.Drawing.Point(200, 160);
            this.AddUSB_button.Name = "AddUSB_button";
            this.AddUSB_button.Size = new System.Drawing.Size(120, 65);
            this.AddUSB_button.TabIndex = 5;
            this.AddUSB_button.Text = "Add USB";
            this.AddUSB_button.UseVisualStyleBackColor = true;
            this.AddUSB_button.Click += new System.EventHandler(this.AddUSB_button_Click);
            // 
            // AddHDD_button
            // 
            this.AddHDD_button.Location = new System.Drawing.Point(30, 160);
            this.AddHDD_button.Name = "AddHDD_button";
            this.AddHDD_button.Size = new System.Drawing.Size(120, 65);
            this.AddHDD_button.TabIndex = 4;
            this.AddHDD_button.Text = "Add HDD";
            this.AddHDD_button.UseVisualStyleBackColor = true;
            this.AddHDD_button.Click += new System.EventHandler(this.AddHDD_button_Click);
            // 
            // AddGPU_button
            // 
            this.AddGPU_button.Location = new System.Drawing.Point(200, 46);
            this.AddGPU_button.Name = "AddGPU_button";
            this.AddGPU_button.Size = new System.Drawing.Size(120, 65);
            this.AddGPU_button.TabIndex = 3;
            this.AddGPU_button.Text = "Add GPU";
            this.AddGPU_button.UseVisualStyleBackColor = true;
            this.AddGPU_button.Click += new System.EventHandler(this.AddGPU_button_Click);
            // 
            // AddRAM_button
            // 
            this.AddRAM_button.Location = new System.Drawing.Point(30, 46);
            this.AddRAM_button.Name = "AddRAM_button";
            this.AddRAM_button.Size = new System.Drawing.Size(120, 65);
            this.AddRAM_button.TabIndex = 2;
            this.AddRAM_button.Text = "Add RAM";
            this.AddRAM_button.UseVisualStyleBackColor = true;
            this.AddRAM_button.Click += new System.EventHandler(this.AddRAM_button_Click);
            // 
            // RemoveLaptop_button
            // 
            this.RemoveLaptop_button.BackColor = System.Drawing.Color.Red;
            this.RemoveLaptop_button.Enabled = false;
            this.RemoveLaptop_button.Location = new System.Drawing.Point(545, 412);
            this.RemoveLaptop_button.Name = "RemoveLaptop_button";
            this.RemoveLaptop_button.Size = new System.Drawing.Size(126, 46);
            this.RemoveLaptop_button.TabIndex = 3;
            this.RemoveLaptop_button.Text = "Remove laptop";
            this.RemoveLaptop_button.UseVisualStyleBackColor = false;
            this.RemoveLaptop_button.Click += new System.EventHandler(this.RemoveLaptop_button_Click);
            // 
            // PurchaseLaptop_button
            // 
            this.PurchaseLaptop_button.BackColor = System.Drawing.Color.Lime;
            this.PurchaseLaptop_button.Enabled = false;
            this.PurchaseLaptop_button.Location = new System.Drawing.Point(419, 412);
            this.PurchaseLaptop_button.Name = "PurchaseLaptop_button";
            this.PurchaseLaptop_button.Size = new System.Drawing.Size(120, 46);
            this.PurchaseLaptop_button.TabIndex = 4;
            this.PurchaseLaptop_button.Text = "Purchase";
            this.PurchaseLaptop_button.UseVisualStyleBackColor = false;
            this.PurchaseLaptop_button.Click += new System.EventHandler(this.PurchaseLaptop_button_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(10, 468);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(122, 20);
            this.label1.TabIndex = 5;
            this.label1.Text = "info purchase: €";
            // 
            // Info_label
            // 
            this.Info_label.AutoSize = true;
            this.Info_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Info_label.Location = new System.Drawing.Point(138, 468);
            this.Info_label.Name = "Info_label";
            this.Info_label.Size = new System.Drawing.Size(18, 20);
            this.Info_label.TabIndex = 6;
            this.Info_label.Text = "0";
            // 
            // group_info_text
            // 
            this.group_info_text.Controls.Add(this.listbox_purchase_info);
            this.group_info_text.Location = new System.Drawing.Point(716, 12);
            this.group_info_text.Name = "group_info_text";
            this.group_info_text.Size = new System.Drawing.Size(252, 416);
            this.group_info_text.TabIndex = 7;
            this.group_info_text.TabStop = false;
            this.group_info_text.Text = "Selected items";
            // 
            // listbox_purchase_info
            // 
            this.listbox_purchase_info.BackColor = System.Drawing.SystemColors.Control;
            this.listbox_purchase_info.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.listbox_purchase_info.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listbox_purchase_info.FormattingEnabled = true;
            this.listbox_purchase_info.Location = new System.Drawing.Point(3, 16);
            this.listbox_purchase_info.Name = "listbox_purchase_info";
            this.listbox_purchase_info.Size = new System.Drawing.Size(246, 397);
            this.listbox_purchase_info.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1024, 497);
            this.Controls.Add(this.group_info_text);
            this.Controls.Add(this.Info_label);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.PurchaseLaptop_button);
            this.Controls.Add(this.RemoveLaptop_button);
            this.Controls.Add(this.group_parts);
            this.Controls.Add(this.group_laptops);
            this.Controls.Add(this.Laptop_listBox);
            this.Name = "Form1";
            this.Text = "Form1";
            this.group_laptops.ResumeLayout(false);
            this.group_parts.ResumeLayout(false);
            this.group_info_text.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox Laptop_listBox;
        private System.Windows.Forms.GroupBox group_laptops;
        private System.Windows.Forms.Button GamingLaptop_button;
        private System.Windows.Forms.Button TravelLaptop_button;
        private System.Windows.Forms.GroupBox group_parts;
        private System.Windows.Forms.Button AddUSB_button;
        private System.Windows.Forms.Button AddHDD_button;
        private System.Windows.Forms.Button AddGPU_button;
        private System.Windows.Forms.Button AddRAM_button;
        private System.Windows.Forms.Button RemoveLaptop_button;
        private System.Windows.Forms.Button PurchaseLaptop_button;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label Info_label;
        private System.Windows.Forms.GroupBox group_info_text;
        private System.Windows.Forms.ListBox listbox_purchase_info;
    }
}

