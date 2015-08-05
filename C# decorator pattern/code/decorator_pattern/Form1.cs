using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace decorator_pattern
{
    public partial class Form1 : Form
    {
        private ILaptop laptopBeingEdited;
        private List<ILaptop> laptopsBought;
        private bool re_edit_laptop = false;
        public Form1()
        {
            InitializeComponent();
            laptopsBought = new List<ILaptop>();
        }

        private void toggleGui()
        {
            if (group_laptops.Enabled)
            {
                group_laptops.Enabled = false;
                group_parts.Enabled = true;
                PurchaseLaptop_button.Enabled = true;
                RemoveLaptop_button.Enabled = true;
                Laptop_listBox.Enabled = false;
            }
            else
            {
                group_laptops.Enabled = true;
                group_parts.Enabled = false;
                PurchaseLaptop_button.Enabled = false;
                RemoveLaptop_button.Enabled = false;
                Laptop_listBox.Enabled = true;
            }
        }

        private void updatePurchaseInfo(string laptopName)
        {
            Info_label.Text = laptopBeingEdited.GetPrice().ToString();
            listbox_purchase_info.Items.Clear();
            string[] info = laptopName.Split('\n');

            foreach (string line in info)
            {
                listbox_purchase_info.Items.Add(line);
            }
        }

        private void GamingLaptop_button_Click(object sender, EventArgs e)
        {
            toggleGui();
            laptopBeingEdited = new GamingLaptop();
            updatePurchaseInfo(laptopBeingEdited.GetProductDetails());
        }

        private void TravelLaptop_button_Click(object sender, EventArgs e)
        {
            toggleGui();
            laptopBeingEdited = new TravelLaptop();
            updatePurchaseInfo(laptopBeingEdited.GetProductDetails());
        }

        private void RemoveLaptop_button_Click(object sender, EventArgs e)
        {
            if (!re_edit_laptop)
            {
                toggleGui();
                laptopBeingEdited = null;
                Info_label.Text = "0";
                listbox_purchase_info.Items.Clear();
            }
            else if (re_edit_laptop)
            {
                toggleGui();
                laptopBeingEdited = null;
                Info_label.Text = "0";
                laptopsBought.RemoveAt(Laptop_listBox.SelectedIndex);
                Laptop_listBox.Items.RemoveAt(Laptop_listBox.SelectedIndex);
                listbox_purchase_info.Items.Clear();
                re_edit_laptop = false;
            }
        }

        private void PurchaseLaptop_button_Click(object sender, EventArgs e)
        {
            if (!re_edit_laptop)
            {
                toggleGui();
                Laptop_listBox.Items.Add(laptopBeingEdited.GetName());
                laptopsBought.Add(laptopBeingEdited);
                laptopBeingEdited = null;
                Info_label.Text = "0";
                listbox_purchase_info.Items.Clear();
            }
            else if (re_edit_laptop)
            {
                toggleGui();
                laptopsBought.RemoveAt(Laptop_listBox.SelectedIndex);
                Laptop_listBox.Items.RemoveAt(Laptop_listBox.SelectedIndex);
                Laptop_listBox.Items.Add(laptopBeingEdited.GetName());
                laptopsBought.Add(laptopBeingEdited);
                laptopBeingEdited = null;
                Info_label.Text = "0";
                listbox_purchase_info.Items.Clear();
                re_edit_laptop = false;
            }
        }

        private void AddGPU_button_Click(object sender, EventArgs e)
        {
            ILaptop tempLaptop = new GPU(laptopBeingEdited);
            laptopBeingEdited = tempLaptop;
            updatePurchaseInfo(laptopBeingEdited.GetProductDetails());
        }

        private void AddRAM_button_Click(object sender, EventArgs e)
        {
            ILaptop tempLaptop = new RAM(laptopBeingEdited);
            laptopBeingEdited = tempLaptop;
            updatePurchaseInfo(laptopBeingEdited.GetProductDetails());
        }

        private void AddUSB_button_Click(object sender, EventArgs e)
        {
            ILaptop tempLaptop = new USB(laptopBeingEdited);
            laptopBeingEdited = tempLaptop;
            updatePurchaseInfo(laptopBeingEdited.GetProductDetails());
        }

        private void AddHDD_button_Click(object sender, EventArgs e)
        {
            ILaptop tempLaptop = new HDD(laptopBeingEdited);
            laptopBeingEdited = tempLaptop;
            updatePurchaseInfo(laptopBeingEdited.GetProductDetails());
        }

        private void Laptop_listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (Laptop_listBox.SelectedIndex >= 0 && Laptop_listBox.SelectedIndex <= laptopsBought.Count && laptopBeingEdited == null)
            {
                laptopBeingEdited = laptopsBought.ElementAt(Laptop_listBox.SelectedIndex);
                updatePurchaseInfo(laptopBeingEdited.GetProductDetails());
                toggleGui();
                re_edit_laptop = true;
            }
        }
    }
}
