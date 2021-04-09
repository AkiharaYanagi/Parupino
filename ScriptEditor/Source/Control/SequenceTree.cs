using System;
using System.ComponentModel;
using System.Windows.Forms;


namespace ScriptEditor
{
	public class SequenceTree : UserControl
	{
		private TreeView treeView1;
		public EditCompend EditCompend { get; set; } = null;

		public SequenceTree ()
		{
			InitializeComponent ();
		}

		private void InitializeComponent ()
		{
			this.treeView1 = new System.Windows.Forms.TreeView();
			this.SuspendLayout();
			// 
			// treeView1
			// 
			this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.treeView1.Location = new System.Drawing.Point(0, 0);
			this.treeView1.Name = "treeView1";
			this.treeView1.Size = new System.Drawing.Size(129, 266);
			this.treeView1.TabIndex = 0;
			this.treeView1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView1_AfterSelect);
			// 
			// SequenceTree
			// 
			this.AutoScroll = true;
			this.Controls.Add(this.treeView1);
			this.Name = "SequenceTree";
			this.Size = new System.Drawing.Size(129, 266);
			this.ResumeLayout(false);

		}

		public void SetCtrl ( EditCompend ec )
		{
			EditCompend = ec;
		}

		public void Set ( BindingDictionary < Sequence > bd_sq )
		{
			if ( null == bd_sq ) { return; }
			treeView1.Nodes.Clear ();

			if ( 0 >= bd_sq.Length() ) { return; }

			TreeNode[] root;

			//アクションのときアクションカテゴリで分類
			BindingList < Sequence > bl = bd_sq.GetBindingList();
			if ( bl[0] is Action ) 
			{
				//アクションカテゴリで初期化
				string[] names = Enum.GetNames ( typeof ( ActionCategory ) );
				root = new TreeNode [ names.Length ];
				int i = 0;
				foreach ( string name in names )
				{
					root [ i ] = new TreeNode ( name );
					++ i;
				}

				//各アクションを分類
				foreach ( Action a in bl )
				{
					string ctg_name = Enum.GetName ( typeof ( ActionCategory ), a.Category );
					int nodeIndex = 0;
					foreach ( TreeNode n in root )
					{
						if ( ctg_name == n.Name )
						{
							nodeIndex = n.Index;
						}
					}
					root [ nodeIndex ].Nodes.Add ( a.Name );
				}
				treeView1.Nodes.AddRange ( root );
			}

			else
			{
				TreeNode [] nodes = new TreeNode [ bl.Count ];
			
				int index = 0;
				foreach ( Sequence s in bl )
				{
					nodes [ index ] = new TreeNode ( s.Name );
					++ index;
				}

				treeView1.Nodes.AddRange ( nodes );

			}
		}

		public void UpdateCategory ( Sequence sq )
		{
			if ( sq is Action )
			{
				Action a = (Action)sq;
				string ctg_name = Enum.GetName ( typeof ( ActionCategory ), a.Category );
				
				//すべてのノードから対象を削除
				foreach ( TreeNode nodes in treeView1.Nodes )
				{
					foreach ( TreeNode n0 in nodes.Nodes )
					{
						if ( a.Name == n0.Text )
						{
							n0.Remove ();
							break;
						}
					}
				}

				//カテゴリの正しい箇所へ追加
				foreach ( TreeNode nodes in treeView1.Nodes )
				{
					if ( ctg_name == nodes.Text )
					{
						nodes.Nodes.Add ( a.Name );
					}
				}

			}
		}

		//ツリー選択時
		private void treeView1_AfterSelect ( object sender, TreeViewEventArgs e )
		{
			string name = treeView1.SelectedNode.Text;

			//アクション名以外のとき何もしない
			EditCompend.SelectSequence ( name );

			DispChara.Inst.Disp ();
		}
	}
}
