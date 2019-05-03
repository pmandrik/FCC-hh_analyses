
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRoot.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootAnalyser.cpp"
#include "/afs/cern.ch/user/p/pmandrik/public/global_cfg/mRootThread.cpp"
#include "tmva_use_comp.C"

struct split_args{
  string inp_name;
  string out_name;
};

void * split_wrapper(void * a){
  split_args * args = (split_args*) a; 
  cout << "Start with " << args->inp_name << endl;
  mRoot::split_tree_tmva(args->inp_name, args->out_name, "ttree", 0.1, 1000);
  cout << "Done with " << args->inp_name << endl;
  // TThread::Exit(0);
  return 0;
}

void tmva_split(string samples_path){
  auto channels = get_channals();

  vector<TThread*> threads;
  for(auto channel : channels){
    split_args * args = new split_args();
    args->inp_name = samples_path + "/" +channel.physic_name + ".root";
    args->out_name = samples_path + "/" +channel.physic_name + "_split.root";
    TThread* new_thread = new TThread(channel.physic_name.c_str(), &split_wrapper, (void*) args);
    threads.push_back( new_thread );
  }

/*
  TThread::Ps();
  cout << "1" << endl;
  threads.at(0)->Run();
  threads.at(1)->Run();
  threads.at(2)->Run();
  threads.at(3)->Run();
  threads.at(4)->Run();
  cout << "2" << endl;

  while(true){
    TThread::Ps();
    cout << "3" << endl;
    gSystem->Sleep(1000);
  }
*/

  threads_care( threads, 10 );
}





