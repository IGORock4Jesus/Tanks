﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tanks
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
		}

		protected override void OnLoad(EventArgs e)
		{
			Renderer.Instance.Initialize(this);
			ResourceManager.Instance.LoadAll();
			LevelConstructor.Instance.Construct(ResourceManager.Instance.GetLevel(1.ToString()));
		}

		protected override void OnFormClosed(FormClosedEventArgs e)
		{
			Renderer.Instance.Dispose();
		}
	}
}